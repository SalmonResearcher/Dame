#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include "Jewel.h"
#include "JewelBullet.h"
#include "EnemySpawn.h"
#include "EnemyAttack.h"
#include "StateManager.h"
#include "EnemyState.h"

#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/VFX.h"
#include "Global.h"

#include <algorithm> // std::maxを使う

//敵のコンフィグファイルみたいなのほしいかも
namespace 
{

	XMFLOAT3 ColliderPosition = { 0.0f,0.0f,0.0f };
	const float COLLIDER_SCALE = 1.25f;

	XMFLOAT3 enemyScale = { 1.0f,1.0f,1.0f };
	const float ATTACK_DISTANCE = 1.5f;	//この値未満まで近づくと攻撃に移行
	const float MOVE_DISTANCE = 2.0f;		//この値を超える距離まで遠ざかると移動

	float moveY = 0.0f;
	float speed_ = 0.0f;

	EnemySpawn* pEnemySpawn;

	float deathPitch;			//倒された音のピッチ
	float hitPitch;				//攻撃を受けたときピッチ
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), pPlayer_(nullptr), isDead_(false),counted_(false)
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

	hDeathSound_ = Audio::Load("Sounds/SE/SlimeDeath.WAV", false, 1);
	assert(hDeathSound_ >= 0);

	hHitSound_ = Audio::Load("Sounds/SE/Attack2.wav", false, 1);
	assert(hHitSound_ >= 0);

	transform_.scale_ = { enemyScale };

	pEnemySpawn = static_cast<EnemySpawn*>(FindObject("EnemySpawn"));
	transform_.position_ = pEnemySpawn->GetSpawnPoint();

	pSpher_ = new SphereCollider(ColliderPosition, COLLIDER_SCALE);
	AddCollider(pSpher_);


	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	pPlayer_ = static_cast<Player*>(FindObject("Player"));

	pStateManager_ = new StateManager(this);

	pStateManager_->AddState("EnemyWalkState", new EnemyWalkState(pStateManager_));
	pStateManager_->AddState("EnemyAttackState", new EnemyAttackState(pStateManager_));
	pStateManager_->AddState("EnemyDeadState", new EnemyDeadState(pStateManager_));

	//初期状態
	pStateManager_->ChangeState("EnemyWalkState");

	Global::SetKillScore(BASE_KILL_SCORE);
}

//更新
void Enemy::Update()
{
	deathPitch = GenerateRandomFloat(MIN_PITCH,MAX_PITCH);
	hitPitch = GenerateRandomFloat(MIN_PITCH, MAX_PITCH);

	//プレイヤーまでの距離
	toPlayerdir_ = sqrtf(pow((target_.x - transform_.position_.x), 2) + pow((target_.z - transform_.position_.z), 2));

	volume_ = SoundDistance(toPlayerdir_);

	// ステートマネージャーの更新
	pStateManager_->Update();


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	if (toPlayerdir_ < MOVE_DISTANCE)
	{
		isNearPlayer_ = true;
	}
	else if(waitTime_ <= 0 && toPlayerdir_ >= ATTACK_DISTANCE)
	{
		isNearPlayer_ = false;
	}

	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}

	else
	{
		KillMe();
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

void Enemy::Walk()
{
	//追いかける＆攻撃するための関数
	target_ = pPlayer_->GetPlayerPosition();
	speed_ = MOVE_SPEED;
	ChasePlayer(target_, speed_);
}

void Enemy::Attack() 
{
	speed_ = ATTACK_MOVE_SPEED;
	ChasePlayer(target_, speed_);

	if ((ATTACK_WAIT_TIME - COLLISION_CREATE_TIME) == waitTime_) {
		AttackCollision();
	}


	if (waitTime_ <= 0)
	{
		waitTime_ = 0;
		isAttackEnd_ = true;
		pStateManager_->ChangeState("EnemyWalkState");
		return;
	}
	waitTime_--;
}

void Enemy::Dead()
{

	if (waitTime_ == DEAD_SOUND_TIME)
	{
		Audio::Play(hDeathSound_, true, deathPitch, volume_);
		CreateVFX(DEATH);
	}

	if (waitTime_ < 0)
	{
		((Player*)FindObject("Player"))->KillCountUp();
		Jewel* pJewel = InstantiateFront<Jewel>(GetParent());
		pJewel->SetPosition(transform_.position_);
		KillMe();
	}
	waitTime_--;

}

void Enemy::AttackCollision() 
{
	EnemyAttack* pEAttack = Instantiate<EnemyAttack>(GetParent());
	pEAttack->SetAttackPosition(transform_.position_);
	pEAttack->SetTime(COLLISION_TIME);
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack" && !isDead_)
	{
		Audio::Play(hHitSound_, true, hitPitch, volume_);
		CreateVFX(HIT);
		waitTime_ = DEAD_WAIT_TIME;
		isDead_ = true;
	}
	if (pTarget->GetObjectName() == "JewelBullet" && !counted_)
	{
		Audio::Play(hHitSound_, true, hitPitch, volume_);
		waitTime_ = DEAD_WAIT_TIME;
		CreateVFX(JEWEL);
		JewelBullet* pBullet = (JewelBullet*)pTarget;
		pBullet->SetKillCount(1);
		isDead_ = true;
		counted_ = true;
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&transform_.position_);

	//ターゲットに向かって伸びているベクトル
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	direction_ = XMVector3Normalize(direction_);

	//direction_の方向にspeedぶん動く
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transform_.position_, newVecPos_);

	// 敵からプレイヤーに向かう方向ベクトルから角度を求める
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); 

	// 角度を度数法に変換する（ラジアンから度に変換）
	angle = XMConvertToDegrees(angle);

	transform_.rotate_.y = angle;
}

void Enemy::JewelDeath()
{
	isDead_ = true;
}


float Enemy::SoundDistance(float distance)
{
	if (distance <= MAX_SOUNDS_DISTANCE)
	{
		return SOUND_VOLUME;
	}
	else if (distance > MAX_SOUNDS_DISTANCE && distance <= FALLOFF)
	{
		//最大音量距離から最小音量距離の間の割合
		float t = (distance - MAX_SOUNDS_DISTANCE) / (FALLOFF - MAX_SOUNDS_DISTANCE);
		return max(MIN_SOUNDS_VOLUME,1.0f * (1.0f - t) / 100 );//100％から最小音量の値が出る
	}
	else
	{
		return MIN_SOUNDS_VOLUME;
	}
}

float Enemy::GenerateRandomFloat(float min, float max)
{
	// 0.0から1.0の範囲の乱数を生成
	float random = static_cast<float>(rand()) / RAND_MAX; 

	// minからmaxの範囲にスケーリング
	return min + random * (max - min); 
}

void Enemy::CreateVFX(STATEVFX svfx) 
{
	switch (svfx) 
	{
	case HIT:
		vfx_.textureFileName = "paticleAssets/flashA_W.png";
		vfx_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + HIT_EFFECT_OFFSET_Y, transform_.position_.z);
		vfx_.number = 1;
		vfx_.positionRnd = XMFLOAT3(0, 0, 0);
		vfx_.direction = XMFLOAT3(0, 0, 0);
		vfx_.directionRnd = XMFLOAT3(0, 0, 0);
		vfx_.size = EFFECT_SIZE_LARGE;
		vfx_.scale = EFFECT_SCALE_DEFAULT;
		vfx_.lifeTime = LIFETIME_SHORT;
		vfx_.speed = 0;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = 0;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	case JEWEL:
		vfx_.textureFileName = "paticleAssets/flashA_B.png";
		vfx_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + HIT_EFFECT_OFFSET_Y, transform_.position_.z);
		vfx_.number = 1;
		vfx_.positionRnd = XMFLOAT3(0, 0, 0);
		vfx_.direction = XMFLOAT3(0, 0, 0);
		vfx_.directionRnd = XMFLOAT3(0, 0, 0);
		vfx_.size = EFFECT_SIZE_LARGE;
		vfx_.scale = EFFECT_SCALE_DEFAULT;
		vfx_.lifeTime = LIFETIME_SHORT;
		vfx_.speed = 0;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = 0;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	case DEATH:
		vfx_.textureFileName = "paticleAssets/star.png";
		vfx_.position = transform_.position_;
		vfx_.number = 3;
		vfx_.positionRnd = POSITION_RND_DEATH;
		vfx_.direction = XMFLOAT3(0, 1, 0);
		vfx_.directionRnd = DIRECTION_RND_DEATH;
		vfx_.size = EFFECT_SIZE_SMALL;
		vfx_.scale = EFFECT_SCALE_SMALL;
		vfx_.lifeTime = LIFETIME_LONG;
		vfx_.speed = EFFECT_SPEED_DEATH;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = EFFECT_GRAVITY;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	default:
		break;
	}
}
void Enemy::DestroyVFX()
{
	stopEmit_ = true;
}

void Enemy::SetAttackTime()
{
	waitTime_ = ATTACK_WAIT_TIME;
}

void Enemy::SetDeadTime()
{
	waitTime_ = DEAD_WAIT_TIME;
}