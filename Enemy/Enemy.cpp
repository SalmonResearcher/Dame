#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Jewel.h"
#include "../JewelBullet.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../EnemyAttack.h"
#include "../EnemySpawn.h"
#include "../Engine/Audio.h"
#include "../Engine/VFX.h"

#include <algorithm> // std::maxを使うために必要

namespace 
{
	XMFLOAT3 CollisionPosition = { 0.0f,0.0f,0.0f };
	float CollisionScale = 1.25f;

	XMFLOAT3 enemyScale = { 1.0f,1.0f,1.0f };
	float attackDistance = 1.5f;
	float moveDistance = 2.0f;

	struct AnimFrame
	{
		int startFrame;
		int endFrame;
		float speed;
	};
	AnimFrame anim1;
	AnimFrame anim2;
	AnimFrame anim3;

	float moveY = 0.0f;
	float speed_ = 0.0f;

	float move = 0.15f;
	float attack = 0.0f;


	int collisionCreateTime = 42;	//攻撃→判定までの時間
	int collisionTime = 3;		//判定の持続フレーム

	int attackWaitTime = 90;
	int deathWaitTime = 60;

	float falloff = 45.0f;		//音が最小になるまでの距離

	EnemySpawn* pEnemySpawn;

	float min = 0.8f;			//音のピッチ
	float max = 1.2f;			//音のピッチ

	float deathPitch;
	float hitPitch;
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), pPlayer(nullptr), counted(false)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("Slime_V2.fbx");
	assert(hModel_ >= 0);

	hDeathSound_ = Audio::Load("SE/SlimeDeath.WAV", false, 1);
	assert(hDeathSound_ >= 0);

	hHitSound_ = Audio::Load("SE/Attack2.wav", false, 1);
	assert(hHitSound_ >= 0);

	transform_.scale_ = { enemyScale };

	pEnemySpawn = static_cast<EnemySpawn*>(FindObject("EnemySpawn"));
	transform_.position_ = pEnemySpawn->GetSpawnPoint();

	pSpher = new SphereCollider(XMFLOAT3(0,0,0), 1.25f);
	AddCollider(pSpher);


	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	pPlayer = static_cast<Player*>(FindObject("Player"));
	
	{
		anim1.startFrame = 0;
		anim1.endFrame = 100;
		anim1.speed = 1;

		anim2.startFrame = 110;
		anim2.endFrame = 200;
		anim2.speed = 1;

		anim3.startFrame = 210;
		anim3.endFrame = 400;
		anim3.speed = 1;
	}

	states = MOVE;
	ChangeAnime(states);
}

//更新
void Enemy::Update()
{
	deathPitch = GenerateRandomFloat(min,max);
	hitPitch = GenerateRandomFloat(min, max);

	//追いかける＆攻撃するための
	target_ = pPlayer->GetPlayerPosition();
	//プレイヤーまでの距離
	toPlayerdir = sqrtf(pow((target_.x - transform_.position_.x), 2) + pow((target_.z - transform_.position_.z), 2));

	volume = SoundDistance(toPlayerdir, falloff);

	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射



	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}

	else
	{
		KillMe();
	}

	switch (states)
	{
	case MOVE:
		speed_ = move;
		ChasePlayer(target_, speed_);

		if (toPlayerdir < moveDistance)
		{
			waitTime_ = attackWaitTime;
			states = ATTACK;
		}

		break;

	case ATTACK:
		speed_ = attack;
		ChasePlayer(target_, speed_);

		if ((attackWaitTime - collisionCreateTime) == waitTime_) {
			Attack();
		}


		if (waitTime_ <= 0 && toPlayerdir >= attackDistance)
		{
			states = MOVE;
			waitTime_ = 0;
		}
		waitTime_--;
		break;

	case DEATH:
		if (waitTime_ == 14)
		{
			Audio::Play(hDeathSound_,true,deathPitch,volume);
			CreateVFX(3);
		}

		if (waitTime_ < 0)
		{
			((Player*)FindObject("Player"))->KillCountUp();
			Jewel* pJewel = InstantiateFront<Jewel>(GetParent());
			pJewel->SetPosition(transform_.position_);
			KillMe();
		}
		waitTime_--;
		break;

	default:
		states = DEATH;
		break;

	}

	if (curState != states)
	{
		ChangeAnime(states);
		curState = states;
	}
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

//開放
void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack" && !isDead)
	{
		CreateVFX(0);
		Death();
	}
	if (pTarget->GetObjectName() == "JewelBullet" && !counted)
	{
		CreateVFX(1);
		JewelBullet* pBullet = (JewelBullet*)pTarget;
		pBullet->SetKillCount(1);
		counted = true;
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&transform_.position_);

	//ターゲットに向かって伸びているベクトル
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	//正規化
	direction_ = XMVector3Normalize(direction_);

	//direction_の方向にspeedぶん動く
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transform_.position_, newVecPos_);

	// 敵からプレイヤーに向かう方向ベクトルから角度を求める
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); // atan2(z, x)を使用して角度を計算

	// 角度を度数法に変換する（ラジアンから度に変換）
	angle = XMConvertToDegrees(angle);

	transform_.rotate_.y = angle;
}


void Enemy::Attack() 
{
	EnemyAttack* pEAttack = Instantiate<EnemyAttack>(GetParent());
	pEAttack->SetAttackPosition(transform_.position_);
	pEAttack->SetTime(collisionTime);
}

void Enemy::Death()
{
	states = DEATH;
	waitTime_ = deathWaitTime;
	isDead = true;
}

void Enemy::JewelDeath()
{
	states = DEATH;
	waitTime_ = deathWaitTime;
	isDead = true;

}

void Enemy::ChangeAnime(STATE state)
{
	switch (state)
	{
	case MOVE:
		Model::SetAnimFrame(hModel_,anim1.startFrame,anim1.endFrame,anim1.speed);
		break;

	case ATTACK:
		Model::SetAnimFrame(hModel_,anim2.startFrame,anim2.endFrame,anim2.speed);
		break;

	case DEATH:
		Model::SetAnimFrame(hModel_,anim3.startFrame,anim3.endFrame,anim3.speed);
		Audio::Play(hHitSound_, true, hitPitch, volume);
		break;

	default:
		states = DEATH;
		break;
	}
}

float Enemy::SoundDistance(float distance, float falloff)
{
	float volume = 0.18f - (distance - 5.0f) / falloff;
	return max(0.0f, volume);
}

float Enemy::GenerateRandomFloat(float min, float max)
{
	float random = static_cast<float>(rand()) / RAND_MAX; // 0.0から1.0の範囲の乱数を生成
	return min + random * (max - min); // minからmaxの範囲にスケーリング
}

void Enemy::CreateVFX(int num)
{
	switch (num) {
	case 0: 
		vfx.textureFileName = "paticleAssets/flashA_W.png";
		vfx.position = XMFLOAT3(transform_.position_.x, transform_.position_.y+0.7f, transform_.position_.z);
		vfx.number = 1;
		vfx.positionRnd = XMFLOAT3(0, 0, 0);
		vfx.direction = XMFLOAT3(0, 0, 0);
		vfx.directionRnd = XMFLOAT3(0, 0, 0);
		vfx.size = XMFLOAT2(4, 4);
		vfx.scale = XMFLOAT2(1.2, 1.2);
		vfx.lifeTime = 5;
		vfx.speed = 0;
		vfx.spin = XMFLOAT3(0, 0, 15.0f);
		vfx.gravity = 0;
		vfx.delay = 0;
		hEmit_ = VFX::Start(vfx);
		break;

	case 1:
		vfx.textureFileName = "paticleAssets/flashA_B.png";
		vfx.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 0.7f, transform_.position_.z);
		vfx.number = 1;
		vfx.positionRnd = XMFLOAT3(0, 0, 0);
		vfx.direction = XMFLOAT3(0, 0, 0);
		vfx.directionRnd = XMFLOAT3(0, 0, 0);
		vfx.size = XMFLOAT2(4, 4);
		vfx.scale = XMFLOAT2(1.2, 1.2);
		vfx.lifeTime = 5;
		vfx.speed = 0;
		vfx.spin = XMFLOAT3(0, 0, 15.0f);
		vfx.gravity = 0;
		vfx.delay = 0;
		hEmit_ = VFX::Start(vfx);
		break;

	case 3:
		vfx.textureFileName = "paticleAssets/star.png";
		vfx.position = (transform_.position_);
		vfx.number = 3;
		vfx.positionRnd = XMFLOAT3(0.8, 0, 0.8);
		vfx.direction = XMFLOAT3(0, 1, 0);
		vfx.directionRnd = XMFLOAT3(15, 15, 15);
		vfx.size = XMFLOAT2(1, 1);
		vfx.scale = XMFLOAT2(0.99, 0.99);
		vfx.lifeTime = 25;
		vfx.speed = 0.4f;
		vfx.spin = XMFLOAT3(0, 0, 15.0f);
		vfx.gravity = 0.02;
		vfx.delay = 0;
		hEmit_ = VFX::Start(vfx);
		break;

	default:
			break;
	}


}

void Enemy::DestroyVFX()
{
	stopEmit_ = true;
}