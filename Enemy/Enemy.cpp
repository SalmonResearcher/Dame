#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../Engine/SphereCollider.h"
//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),hStage_(-1),startFrame(0),endFrame(100),animeSpeed(1)
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

	transEnemy_.scale_ = { 0.7f ,0.7f,0.7f};

	transEnemy_.position_.x = target_.x;
	transEnemy_.position_.y = target_.y;
	transEnemy_.position_.z = 5;

	SphereCollider* pSpher = new SphereCollider(XMFLOAT3(0,0.8f,0), 1.25f);
	AddCollider(pSpher);
	states = MOVE;
	prevState = states;
}

//更新
void Enemy::Update()
{
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();



	RayCastData data;
	data.start = { transEnemy_.position_.x,0,transEnemy_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射


	if (data.hit)
	{
		transEnemy_.position_.y = -data.dist;
	}

	switch (states)
	{
	case MOVE:
		target_ = ((Player*)FindObject("Player"))->GetPlayerPos();
		ChasePlayer(target_, 0.1f);
		Debug::Log("距離？＝");
		Debug::Log(sqrtf(pow((target_.x - transEnemy_.position_.x),2) +
			pow((target_.z - transEnemy_.position_.z), 2)),true);
		
		break;

	case ATTACK:
		break;

	case DEATH:
		break;

	default:
		states = DEATH;
		break;

	}
	//transEnemy_.position_.z += 0.03f;

	//プレイヤーのもとに駆け付けられるように
	//SetTargetPosition()


	transform_.position_ = transEnemy_.position_;
	prevState = states;
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transEnemy_);
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
	vPosition_ = XMLoadFloat3(&transEnemy_.position_);

	//ターゲットに向かって伸びているベクトル
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	//正規化
	direction_ = XMVector3Normalize(direction_);

	//direction_の方向にspeedぶん動く
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transEnemy_.position_, newVecPos_);

	// 敵からプレイヤーに向かう方向ベクトルから角度を求める
	float angle = atan2( XMVectorGetX(direction_), XMVectorGetZ(direction_)); // atan2(z, x)を使用して角度を計算

	// 角度を度数法に変換する（ラジアンから度に変換）
	angle = XMConvertToDegrees(angle);

	transEnemy_.rotate_.y = angle;
}

void Enemy::AttackPlayer()
{
}

void Enemy::Death() 
{
	
}