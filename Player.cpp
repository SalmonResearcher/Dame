#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "Stage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"
#include <string>

//エンジンの機能
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

//#include "math.h"

namespace {
	//プレイヤーの大きさ。
	// 基本的には中央が原点なので2で割る。
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	float mouseSens = 1;

    int attackWaitTime = 20;			//攻撃時の待ち時間
	int attackCountDown = 0;			//攻撃時のカウントダウン
    const float JEWEL_WEIGHT = 0.01f;

    const float MAXSPEED = 0.15f;		//カメラの回転速度,プレイヤーの移動速度
    float speed = 0.0f;
	int walking = 1;
    int dash = 2;
    bool isHit;

	float jumpVelocity = 0.2f;
	float gravity = 0.01f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	float min = 0.9f;
	float max = 1.1f;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0), weight_(0), killCount_(0), jewelDeliver_(0), pStateManager_(nullptr)
	, attackEnd(false)
{
}

void Player::Initialize()
{
  	hModel_ = Model::Load("NewPlayer.fbx");
	assert(hModel_ >= 0);

	hSound_ = Audio::Load("SE/SordBig.wav", false, 2);

	hGetSound_ = Audio::Load("SE/GetJewel.wav", false, 1);

	// ステートマネージャー
	pStateManager_ = new StateManager(this);

	//カメラ
	pCamera_ = Instantiate<PlayerCamera>(this);

	BoxCollider* collider = new BoxCollider({0,0.5,0},{1.0,1.0,1.0});
	AddCollider(collider);

	// あらかじめ状態インスタンスを生成して登録
	pStateManager_->AddState("IdleState", new IdleState(pStateManager_));
	pStateManager_->AddState("WalkState", new WalkState(pStateManager_));
	pStateManager_->AddState("RunState", new RunState(pStateManager_));
	pStateManager_->AddState("JumpState", new JumpState(pStateManager_));
	pStateManager_->AddState("AttackState", new AttackState(pStateManager_));
	pStateManager_->AddState("KnockbackState", new KnockbackState(pStateManager_));

	//初期状態
	pStateManager_->ChangeState("IdleState");
}

Player::~Player()
{
	SAFE_DELETE(pStateManager_);
}

void Player::Update()
{
	//ランダム
	jewelPitch = GenerateRandomFloat(min, max);

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	// ステートマネージャーの更新
	pStateManager_->Update();


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	RayCastData play;
	play.start = { transform_.position_.x,transform_.position_.y + 0.5f,transform_.position_.z };   //レイの発射位置
	play.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &play); //レイを発射

	if (data.hit)
	{
		if (InputManager::IsJump() && !isJumping_)
		{
			Jump();
		}

		else if (isJumping_)
		{
			AddGravity();
		}

		//ジャンプ後地面に触ったら
		if (play.dist < 0.4 && isJumping_)
		{
			moveY_ = 0.0f;
			isJumping_ = false;
		}

		//ジャンプしていない,地に足がつくなら
		if (!isJumping_ && play.hit)
		{
			transform_.position_.y = -data.dist;
		}

		//地に足がつかないのならば
		else if (!play.hit)
		{
			isJumping_ = true;
		}

		//Y座標移動
		transform_.position_.y += moveY_;

	}

	// ステージ外に落ちてしまった場合のリセット
	if (transform_.position_.y <= -100)
	{
		transform_.position_ = { 0, -data.dist, 0 };
		moveY_ = 0;
	}

	// Y座標の更新
	transform_.position_.y += moveY_;

if (InputManager::IsWalk())
{
	speed += 0.006f;
	if (speed >= MAXSPEED)
	{
		speed = MAXSPEED;
	}
}
else
{
	speed -= 0.01f;
	if (speed <= 0)
	{
		speed = 0;
	}
}

	if (Input::IsMouseButton(1))
	{
		RotatePlayer();
	}

	// 左クリックと右クリックが同時に押され、ジュエルが1つ以上ある場合にジュエルバレットを生成
	if ((InputManager::IsShootJewel()) && jewelCount_ > 0)
	{
		JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());

		// プレイヤーの回転行列を作成
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// プレイヤーの前方ベクトルを取得
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);

		// ジュエルバレットの方向、位置、回転を設定
		pJB->BulletDirection(playerForwardVector);
		pJB->BulletPosition(transform_.position_);
		pJB->BulletRotate(transform_.rotate_);

		// ジュエルカウントを減少
		jewelCount_--;
	}

	//重さの最大
	weight_ = 1 - min(0.99, jewelCount_ * JEWEL_WEIGHT);

	Debug::Log("速度＝");
	Debug::Log(speed * dash * weight_, true);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::Walk()
{
	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, walking);
	RotatePlayer(moveVector);
}

void Player::Jump()
{
	//地面に足がついているとき
	if (!isJumping_)
	{
		isJumping_ = true;
		moveY_ += jumpVelocity * weight_;
	}
}

void Player::Run()
{

	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, dash);
	RotatePlayer(moveVector);
}
void Player::AddGravity()
{
	//自由落下
	moveY_ -= 0.01;

	if (moveY_ <= -0.2f)
	{
		moveY_ = -0.2f;
	}
}

void Player::AddMovement(XMVECTOR moveVector, float run)
{
	XMVECTOR newPosition = XMLoadFloat3(&transform_.position_) + (moveVector * run);
	XMStoreFloat3(&transform_.position_, newPosition);
}

// 移動計算を行う関数
XMVECTOR Player::CalcMovementInput()
{
	// 移動ベクトル
	XMVECTOR moveVector = XMVectorZero();
	XMVECTOR forwardMove = XMVectorZero();
	XMVECTOR sideMove = XMVectorZero();

	// カメラのY軸回転行列を取得
	XMMATRIX rotMatY = pCamera_->GetRotateY();



	// 前後の移動
	if (InputManager::IsMoveForward())
	{
		forwardMove = XMVectorSet(0, 0, speed* weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}
	if (InputManager::IsMoveBackward())
	{
		forwardMove = XMVectorSet(0, 0, -speed * weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}

	// 左右の移動
	if (InputManager::IsMoveLeft())
	{
		sideMove = XMVectorSet(-speed * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}
	if (InputManager::IsMoveRight())
	{
		sideMove = XMVectorSet(speed * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}

	return moveVector;
}

void Player::Attacking()
{
	// 攻撃クールダウンを設定
	if (attackCountDown == 0)
	{
		attackCountDown = attackWaitTime;
		attackEnd = false;
		Audio::Play(hSound_,2.0f);
	}
	else
	{
		attackCountDown--;
	}

	// 攻撃カウントダウンが特定の値以下で、攻撃が終了していない場合に攻撃を生成(ややこい)
	if (attackCountDown <= 13 && !attackEnd)
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		// プレイヤーの回転行列を作成
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// プレイヤーの前方ベクトルを取得
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);

		pAtk->AttackDirection(playerForwardVector);
		pAtk->AttackPosition(transform_.position_);

		//なぜかここの数字を変更すると当たり判定の数が増える...謎。
		pAtk->SetDeleteTime(1);
	}

	// 攻撃カウントダウンが0以下なら攻撃終了
	if (attackCountDown <= 0)
	{
		attackEnd = true;
	}
}

void Player::Knockback()
{
}

bool Player::IsJumping()
{
	return isJumping_;
}

bool Player::IsAttackEnd()
{
	return attackEnd;
}

void Player::OnCollision(GameObject* pTarget)
{
	isHit = false;

	if (pTarget->GetObjectName() == "Jewel")
	{
		//ここでエフェクトも
		Audio::Play(hGetSound_, true, jewelPitch, 1.0f);
		pTarget->KillMe();
		jewelCount_++;
	}

	if (pTarget->GetObjectName() == "JewelBox")
	{
		if (Input::IsKey(DIK_E))
		{
			if (onCollisionTime % 5 == 0 && !(jewelCount_ < 0))
			{
				jewelCount_--;
				jewelDeliver_++;
				onCollisionTime = 0;
			}
			onCollisionTime++;
		}
	}

	if (pTarget->GetObjectName() == "EnemyAttack")
	{
		knock = 0.8f;
		isJumping_ = true;
		moveY_ += 0.1f;

		// プレイヤーの前方ベクトルを取得
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
		//vecPlayer_ += playerBackVector;
		//XMStoreFloat3(&transform_.position_, vecPlayer_);
	}
}

int Player::GetJewelCount()
{
	return jewelCount_;
}

void Player::KillCountUp()
{
	killCount_++;
}
int Player::GetKillCount()
{
	return killCount_;
}

XMVECTOR Player::GetKnockbackDirection()
{
	// プレイヤーの前方ベクトルを取得
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	XMConvertToRadians(transform_.rotate_.y),XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
	//vecPlayer_ += playerBackVector;
	return playerBackVector;
}

float Player::GetSpeed()
{
	return speed;
}

float Player::GetWeight()
{
	return weight_;
}

void Player::RotatePlayer(XMVECTOR moveVector)
{
	// 移動ベクトルから水平方向の角度を計算
	XMFLOAT3 moveVecFloat3;
	XMStoreFloat3(&moveVecFloat3, moveVector);

	if (moveVecFloat3.x != 0 || moveVecFloat3.z != 0) {
		float playerYaw = atan2f(moveVecFloat3.x, moveVecFloat3.z);
		transform_.rotate_.y = XMConvertToDegrees(playerYaw);
	}

	// プレイヤーの回転行列を作成
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));
}

void Player::RotatePlayer()
{
	// カメラの回転行列からプレイヤーの水平方向の角度を求める
	XMFLOAT4X4 cameraRot = pCamera_->GetCameraRotateMatrix();
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	// プレイヤーの回転を更新
	transform_.rotate_.y = XMConvertToDegrees(playerYaw);

	// プレイヤーの回転行列を作成
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));
}

float Player::GenerateRandomFloat(float min, float max) 
{
	float random = static_cast<float>(rand()) / RAND_MAX; // 0.0から1.0の範囲の乱数を生成
	return min + random * (max - min); // minからmaxの範囲にスケーリング
}