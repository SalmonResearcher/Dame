#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../EnemyAttack.h"


//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), startFrame(0), endFrame(100), animeSpeed(1)
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

	tEnemy_.scale_ = { 0.7f ,0.7f,0.7f };

	tEnemy_.position_.x = target_.x;
	tEnemy_.position_.y = target_.y;
	tEnemy_.position_.z = 5;

	AddCollider(pSpher);
	Model::SetAnimFrame(hModel_, 0, 100, 1);
	states = MOVE;

	EnemyAttack* pEAtk = Instantiate<EnemyAttack>(GetParent());
	pEAtk->SetTime();

}

//更新
void Enemy::Update()
{
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	Model::GetBonePosition(hModel_, "AttackPos");

	RayCastData data;
	data.start = { tEnemy_.position_.x,0,tEnemy_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射


	if (data.hit)
	{
		tEnemy_.position_.y = -data.dist;
	}

	switch (states)
	{
	case MOVE:
		target_ = ((Player*)FindObject("Player"))->GetPlayerPos();
		toPlayerdir = sqrtf(pow((target_.x - tEnemy_.position_.x), 2) + pow((target_.z - tEnemy_.position_.z), 2));


		ChasePlayer(target_, 0.1f);
		if (toPlayerdir < 0.5f)
		{
			states = ATTACK;
		}

		Debug::Log("toPlayerDir = ");
		Debug::Log(toPlayerdir, true);
		break;

	case ATTACK:
		AttackPlayer();
		bonepos = Model::GetBonePosition(hModel_, "middle");
		transform_.position_ = (bonepos);
		break;

	case DEATH:
		break;

	default:
		states = DEATH;
		break;

	}
	//tEnemy_.position_.z += 0.03f;

	//プレイヤーのもとに駆け付けられるように
	//SetTargetPosition()


	if (curState != states)
	{
		ChangeAnime(states);
		curState = states;
	}
	transform_.position_ = tEnemy_.position_;
	
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, tEnemy_);
	Model::Draw(hModel_);

}

//開放
void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack")
	{
		Death();
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&tEnemy_.position_);

	//ターゲットに向かって伸びているベクトル
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	//正規化
	direction_ = XMVector3Normalize(direction_);

	//direction_の方向にspeedぶん動く
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&tEnemy_.position_, newVecPos_);

	// 敵からプレイヤーに向かう方向ベクトルから角度を求める
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); // atan2(z, x)を使用して角度を計算

	// 角度を度数法に変換する（ラジアンから度に変換）
	angle = XMConvertToDegrees(angle);

	tEnemy_.rotate_.y = angle;
}

void Enemy::AttackPlayer()
{
}

void Enemy::Death()
{

}

void Enemy::ChangeAnime(STATE state)
{
	switch (state)
	{
	case MOVE:
		Model::SetAnimFrame(hModel_, 0, 100, 1);
		break;

	case ATTACK:
		Model::SetAnimFrame(hModel_, 110, 140, 1);
		break;

	case DEATH:
		Model::SetAnimFrame(hModel_, 150, 175, 1);
		break;

	default:
		states = DEATH;
		break;
	}
}

