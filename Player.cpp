#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "Stage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"

//エンジンの機能
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"

//
//#include "math.h"

namespace {
	//プレイヤーの大きさ。
// 基本的には中央が原点なので2で割る。
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	float mouseSens = 1;

    float attackStart;
    float attackEnd;
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //カメラの回転速度,プレイヤーの移動速度
    float speed_ = 0;
    int dash_ = 1;
    bool isHit;

    int onCollisionTime = 0;


	Transform tCamera;  //カメラのトランスフォーム

	XMFLOAT3 movePlayer;

	XMFLOAT3 Camposition_;
	XMFLOAT3 smoothCam;

	bool isKockBack = false;
	float knock;

	struct AnimFrame {
		int startFrame;
		int endFrame;
		int animSpeed;
	};
	AnimFrame wait, slowMove, move, fastMove, attack;

}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0),weight_(0),killCount_(0),jewelDeliver_(0),pStateManager_(nullptr)
{
}

void Player::Initialize()
{
  	hModel_ = Model::Load("NewPlayer.fbx");
	assert(hModel_ >= 0);

	// ステートマネージャー
	pStateManager_ = new StateManager(this);

	//カメラ
	pCamera_ = Instantiate<PlayerCamera>(this);

	BoxCollider* collider = new BoxCollider({0,0.5,0},{1.0,1.0,1.0});
	AddCollider(collider);

	{
		wait.startFrame = 0;
		wait.endFrame = 120;
		wait.animSpeed = 1;

		slowMove.startFrame = 140;
		slowMove.endFrame = 230;
		slowMove.animSpeed = 1;

		move.startFrame = 280;
		move.endFrame = 330;
		move.animSpeed = 1;

		fastMove.startFrame = 340;
		fastMove.endFrame = 365;
		fastMove.animSpeed = 1;

		attack.startFrame = 370;
		attack.endFrame = 390;
		attack.animSpeed = 1;
	}


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
	// ステートマネージャーの更新
	pStateManager_->Update();
	if (isJumping_)
	{
		//juuryoku
	}

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = {transform_.position_.x,0,transform_.position_.z};   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	RayCastData play;
	play.start = { transform_.position_.x,transform_.position_.y+0.3f,transform_.position_.z };   //レイの発射位置
	play.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &play); //レイを発射
	
	if (data.hit)
	{
		//ジャンプ
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping_)
		{
			isJumping_ = true;
			moveY_ += 0.2f * weight_;
		}
		
		else if (isJumping_)
		{
			//自由落下
			moveY_ -= 0.01;

			if (moveY_ <= -0.25f)
			{
				moveY_ = -0.25f;
			}
		}

		//ジャンプ後地面に触ったら
		if (play.dist <= 0.25 && isJumping_)
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



	if (Input::IsKey(DIK_LSHIFT))
		dash_ = 2;

	else
		dash_ = 1;

	static bool debug = true;



	//マウス感度
	{
		if (Input::IsKeyDown(DIK_UP))
		{
			if (Input::IsKey(DIK_LSHIFT))
				mouseSens += 0.5f;
			else
				mouseSens += 0.1f;
		}

		if (Input::IsKeyDown(DIK_DOWN))
		{
			if (Input::IsKey(DIK_LSHIFT))
				mouseSens -= 0.5f;
			else
				mouseSens -= 0.1f;
		}
	}
	//マウス位置固定
	if (debug)
		SetCursorPos(800, 400);

	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 camMove = { 0,0,0 };

	//マウスの移動量
	move.x += Input::GetMouseMove().x * mouseSens;
	move.y += Input::GetMouseMove().y * mouseSens;
	move.z += Input::GetMouseMove().z * mouseSens;	//マウスホイール



	//マウスの移動量に応じてカメラを回転させる
	camMove.y = move.x;
	camMove.x = move.y;

	

	//マウスセンシティビリティ
	camMove.x *= 0.1;
	camMove.y *= 0.1;

	//下を向きすぎないように
	if (camMove.x >= 75)
	{
		camMove.x = 75;
		move.y = 750;
	}

	//上を向きすぎない
	if (camMove.x <= -85)
	{
		camMove.x = -85;
		move.y = -850;
	}

	tCamera.rotate_ = camMove;
	//プレイヤー移動↓
	/*
	//Y軸の回転行列
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(tCamera.rotate_.y));

	//X軸の回転軸
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(tCamera.rotate_.x));

	//移動ベクトル
	XMVECTOR nowVec = XMLoadFloat3(& transform_.position_);			//今のカメラ位置座標
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash_ * weight_, 0);		//z座標に動く速度
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y軸回転行列をfrontmoveベクトルへ変換

	//左右
	XMVECTOR sideVec_ = XMVectorSet(speed_ * dash_ * weight_, 0, 0, 0);
	sideVec_ = XMVector3TransformCoord(sideVec_, rotMatY);

	//プレイヤーもここで移動させる
	vecPlayer_ = XMLoadFloat3(&transform_.position_);

	if ((Input::IsKey(DIK_W)|| Input::IsKey(DIK_A)|| Input::IsKey(DIK_S)|| Input::IsKey(DIK_D)))
	{
		speed_ += 0.01f;
		if (speed_ >= MAXSPEED)
			speed_ = MAXSPEED;
	}
	else
	{
		speed_ -= 0.01f;
		if (speed_ <= 0.0f)
		{
			speed_ = 0.0f;
		}
	}

	//プレイヤー移動
	if (Input::IsKey(DIK_W))
	{
		vecPlayer_ += frontMove;

	}

	if (Input::IsKey(DIK_S))
	{
		vecPlayer_ -= frontMove;
	}

	if (Input::IsKey(DIK_A))
	{
		vecPlayer_ -= sideVec_;
	}

	if (Input::IsKey(DIK_D))
	{
		vecPlayer_ += sideVec_;
	}

	XMVector3Normalize(vecPlayer_);
	XMStoreFloat3(&transform_.position_, vecPlayer_);
	*/

	/*
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);			//今のカメラ位置座標

	//カメラ移動
	XMStoreFloat3(&tCamera.position_, nowVec);

	//カメラ本体
	XMVECTOR vCam = { 0,2,-10,0 };

	//カメラ注視点
	XMFLOAT3 camTarget = transform_.position_;

	Camera::SetTarget(camTarget);

	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//カメラ座標変更
	XMStoreFloat3(&Camposition_, nowVec + vCam);
	
	//カメラ移動
	Camera::SetPosition(Camposition_);

	*/

	XMFLOAT4X4 cameraRot = pCamera_->GetCameraRotateMatrix();

	//プレイヤーの水平方向の角度を求める
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	//// プレイヤーの回転を更新
	transform_.rotate_.y = XMConvertToDegrees(playerYaw);

	// プレイヤーの回転行列を作成
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));

	// プレイヤーの前方ベクトルを取得
	XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);


	//くりっくしたら
	if (Input::IsMouseButtonDown(0) && !(Input::IsMouseButton(1)))
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		//pAtk->SetMove(camTarget);
		//pAtk->SetPosition(camTarget);
		pAtk->SetTime(2);

	}
	else if (Input::IsMouseButtonDown(0) && (Input::IsMouseButton(1)) && jewelCount_ > 0)
	{
		JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());
		// プレイヤーの回転行列を作成
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// プレイヤーの前方ベクトルを取得
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),playerRotMat);
		pJB->BulletDirection(playerForwardVector);
		pJB->BulletPosition(transform_.position_);
		pJB->BulletRotate(transform_.rotate_);
		jewelCount_--;
	}

	//重さの最大
	weight_ = 1 - min(0.99, jewelCount_ * JEWEL_WEIGHT);

	transform_ = transform_;
	transform_.rotate_ = transform_.rotate_;
}



void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
	//if (currentState_) {
	//	delete currentState_;
	//}
}

void Player::Walk()
{
	AddMovement(CalcMovementInput(),dash_);
}

void Player::Jump()
{
}

void Player::Run()
{
}
void Player::AddGravity()
{

}
void Player::AddMovement(XMVECTOR moveVector, float run)
{
	XMStoreFloat3(&transform_.position_, moveVector * run);
}

// 移動計算を行う関数
XMVECTOR Player::CalcMovementInput()
{
	if ((Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D)))
	{
		speed_ += 0.01f;
		if (speed_ >= MAXSPEED)
			speed_ = MAXSPEED;
	}
	else
	{
		speed_ -= 0.01f;
		if (speed_ <= 0.0f)
		{
			speed_ = 0.0f;
		}
	}



	// 計算結果
	XMVECTOR vecPlayer_;

	XMMATRIX rotMatY = pCamera_->GetRotateY();

	//移動ベクトル
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);			//今のカメラ位置座標
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash_ * weight_, 0);		//z座標に動く速度
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y軸回転行列をfrontmoveベクトルへ変換

	//左右
	XMVECTOR sideVec_ = XMVectorSet(speed_ * dash_ * weight_, 0, 0, 0);
	sideVec_ = XMVector3TransformCoord(sideVec_, rotMatY);

	//プレイヤーもここで移動させる
	vecPlayer_ = XMLoadFloat3(&transform_.position_);

	// PlayerクラスのMove関数内の一部
	if (InputManager::IsMoveForward())
	{
		vecPlayer_ += frontMove;
	}
	if (InputManager::IsMoveLeft())
	{
		vecPlayer_ -= sideVec_;
	}
	if (InputManager::IsMoveBackward())
	{
		vecPlayer_ -= frontMove;
	}
	if (InputManager::IsMoveRight())
	{
		vecPlayer_ += sideVec_;
	}


	if (speed_ >= MAXSPEED)
	{
		speed_ = MAXSPEED;
	}

	XMVector3Normalize(vecPlayer_);
	return vecPlayer_;
}

void Player::Attacking()
{
}

void Player::Knockback()
{
}

bool Player::IsJumping()
{
	return false;
}


//void Player::ChangeState(PlayerState* newState)
//{
//	if (currentState_) {
//		currentState_->Exit(this);
//		delete currentState_;
//	}
//	currentState_ = newState;
//	if (currentState_) {
//		currentState_->Enter(this);
//	}
//}

void Player::OnCollision(GameObject* pTarget)
{
	isHit = false;

	if (pTarget->GetObjectName() == "Jewel")
	{
		//ここでエフェクトも
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
		//isJumping = true;
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

XMVECTOR  Player::GetKnockbackDirection()
{
	// プレイヤーの前方ベクトルを取得
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	XMConvertToRadians(transform_.rotate_.y),XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
	//vecPlayer_ += playerBackVector;;
	return playerBackVector;
}