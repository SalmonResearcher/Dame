#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../JewelBullet.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../EnemyAttack.h"

namespace 
{
	XMFLOAT3 CollisionPosition = { 0.0f,0.0f,0.0f };
	float CollisionScale = 1.25f;

	XMFLOAT3 enemyScale = { 0.7f,0.7f,0.7f };

	struct AnimFrame
	{
		int startFrame;
		int endFrame;
		float speed;
	};
	AnimFrame anim1;
	AnimFrame anim2;
	AnimFrame anim3;

	int attackWaitTime = 20;
	int deathWaitTime = 20;
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1),pPlayer(nullptr)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("Slime.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { enemyScale };

	transform_.position_.x = target_.x;
	transform_.position_.y = target_.y;
	transform_.position_.z = 15;

	pSpher = new SphereCollider(XMFLOAT3(0,0,0), 1.25f);
	AddCollider(pSpher);

	states = MOVE;

	EnemyAttack* pEAtk = Instantiate<EnemyAttack>(GetParent());
	pEAtk->SetTime();

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	pPlayer = static_cast<Player*>(FindObject("Player"));
	{
		anim1.startFrame = 0;
		anim1.endFrame = 100;
		anim1.speed = 1;

		anim2.startFrame = 110;
		anim2.endFrame = 140;
		anim2.speed = 0.8;

		anim3.startFrame = 150;
		anim3.endFrame = 175;
		anim3.speed = 1;
	}
}

//更新
void Enemy::Update()
{
	//追いかける＆攻撃するための
	target_ = pPlayer->GetPlayerPos();
	//プレイヤーまでの距離
	toPlayerdir = sqrtf(pow((target_.x - transform_.position_.x), 2) + pow((target_.z - transform_.position_.z), 2));


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射



	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}

	switch (states)
	{
	case MOVE:
		speed_ = 0.1f;
		ChasePlayer(target_, speed_);

		if (toPlayerdir < 5.0f)
		{
			waitTime_ = 36;
			states = ATTACK;
		}

		break;

	case ATTACK:
		speed_ = 0.0f;
		Attack();
		ChasePlayer(target_, speed_);

		if (waitTime_ <= 0 && toPlayerdir >= 4.0f)
		{
			states = MOVE;
			waitTime_ = 0;
		}
		waitTime_--;
		break;

	case DEATH:
		if (waitTime_ <= 0)
		{
			((Player*)FindObject("Player"))->KillCountUp();
			KillMe();
		}
		waitTime_--;
		break;

	default:
		states = DEATH;
		break;

	}
	transform_.position_.z += 0.03f;

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
		waitTime_ = 20;
		Death();
	}
	if (pTarget->GetObjectName() == "JewelBullet" && !isDead)
	{
		Death();
		waitTime_ = 20;
		JewelBullet* pBullet = (JewelBullet*)pTarget;
		pBullet->SetKillCount(1);
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

}

void Enemy::Death()
{
	states = DEATH;
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
		break;

	default:
		states = DEATH;
		break;
	}
}
