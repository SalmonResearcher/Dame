#include "Player.h"
#include "Attack.h"
#include "Jewel.h"
#include "JewelBullet.h"
#include "Enemy.h"
#include "Stage.h"
#include "TutorialStage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"
#include "Global.h"
#include <string>

//エンジンの機能
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Debug.h"
//#include "math.h"

namespace {
	//プレイヤーの大きさ。
	// 基本的には中央が原点なので2で割る。
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	// 攻撃時の待ち時間とカウントダウン
	const int ATTACK_WAIT_TIME = 20;


	//これグローバルのほうがいいかも..?
    const float JEWEL_WEIGHT = 0.01f;

	// プレイヤーの加速度
	const float PLAYER_ACCELERATION = 0.006f;

	const float MAX_SPEED = 0.15f;

	const int WALKING_SPEED = 1;
	const int DASH_SPEED = 2;

	const float JUMP_VELOCITY = 0.4f;
	const float GRAVITY = 0.02f;
	const float MAX_GRAVITY = 0.5f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	//音のピッチ
	float min = 0.9f;
	float max = 1.1f;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0), weight_(0), killCount_(0), jewelDeliver_(0), pStateManager_(nullptr)
	, attackEnd_(false)
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
	jewelPitch_ = GenerateRandomFloat(min, max);

	hStage_ = SetStageHandle();

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

	Debug::Log(play.dist, true);

	// 地面有り
	if (data.hit)
	{
		// ジャンプしていないとき
		if (InputManager::IsJump() && !isJumping_)
		{
			Jump();
		}
		// ジャンプしていたら
		else if (isJumping_)
		{
			AddGravity();

			// ジャンプ後地面に触ったら
			if (play.dist < 0.498f)
			{
				moveY_ = 0.0f;
				isJumping_ = false;
				transform_.position_.y = -data.dist;  // 地面に位置を固定
			}
		}
		else // ジャンプしていない, 地に足がつくなら
		{
			if (play.hit)
			{
				transform_.position_.y = -data.dist;
			}
			else // 地に足がつかないのならば
			{
				isJumping_ = true;
			}
		}
	}
	else // 地面がない場合
	{
		AddGravity();
	}

	// ステージ外に落ちてしまった場合のリセット
	if (transform_.position_.y <= -90)
	{
		transform_.position_ = { 0, -data.dist, 0 };
		moveY_ = 0;
	}

	// Y座標の更新
	transform_.position_.y += moveY_;

	// 移動速度の管理
	if (InputManager::IsWalk())
	{
		speed_ += PLAYER_ACCELERATION;
		if (speed_ >= MAX_SPEED)
		{
			speed_ = MAX_SPEED;
		}
	}
	else
	{
		speed_ -= 0.01f;
		if (speed_ <= 0)
		{
			speed_ = 0;
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
	AddMovement(moveVector, WALKING_SPEED);
	RotatePlayer(moveVector);
}

void Player::Jump()
{
	//地面に足がついているとき
	if (!isJumping_)
	{
		isJumping_ = true;
		moveY_ += JUMP_VELOCITY * weight_;
	}
}

void Player::Run()
{

	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, DASH_SPEED);
	RotatePlayer(moveVector);
}
void Player::AddGravity()
{
	//自由落下
	moveY_ -= GRAVITY;

	if (moveY_ <= -MAX_GRAVITY)
	{
		moveY_ = -MAX_GRAVITY;
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
		forwardMove = XMVectorSet(0, 0, speed_* weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}
	if (InputManager::IsMoveBackward())
	{
		forwardMove = XMVectorSet(0, 0, -speed_ * weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}

	// 左右の移動
	if (InputManager::IsMoveLeft())
	{
		sideMove = XMVectorSet(-speed_ * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}
	if (InputManager::IsMoveRight())
	{
		sideMove = XMVectorSet(speed_ * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}

	return moveVector;
}

void Player::Attacking()
{
	// 攻撃クールダウンを設定
	if (attackCountDown_ == 0)
	{
		attackCountDown_ = ATTACK_WAIT_TIME;
		attackEnd_ = false;
		Audio::Play(hSound_,true,2.0f,Global::SE_VOLUME);
	}
	else
	{
		attackCountDown_--;
	}

	// 攻撃カウントダウンが特定の値以下で、攻撃が終了していない場合に攻撃を生成(ややこい)
	if (attackCountDown_ <= 13 && !attackEnd_)
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
	if (attackCountDown_ <= 0)
	{
		attackEnd_ = true;
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
	return attackEnd_;
}

void Player::OnCollision(GameObject* pTarget)
{
	isHit_ = false;

	if (pTarget->GetObjectName() == "Jewel")
	{
		((Jewel*)FindObject("Jewel"))->DestroyVFX();
		Audio::Play(hGetSound_, true, jewelPitch_, Global::SE_VOLUME);
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
	return speed_;
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

//ランダムなFloatのmin～maxの値を算出
float Player::GenerateRandomFloat(float min, float max) 
{
	float random = static_cast<float>(rand()) / RAND_MAX; // 0.0から1.0の範囲の乱数を生成
	return min + random * (max - min); // minからmaxの範囲にスケーリング
}

int Player::SetStageHandle()
{
	if ((FindObject("Stage")) != nullptr)
	{
		return ((Stage*)FindObject("Stage"))->GetModelHandle();
	}
	else if ((FindObject("TutorialStage")) != nullptr)
	{
		return ((TutorialStage*)FindObject("TutorialStage"))->GetModelHandle();
	}
	return -1;
}