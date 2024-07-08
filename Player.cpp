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

//
//#include "math.h"

namespace {
	//プレイヤーの大きさ。
// 基本的には中央が原点なので2で割る。
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	float mouseSens = 1;

    int attackWaitTime = 20;	//攻撃時の待ち時間
	int attackCountDown = 0;	//攻撃時のカウントダウン
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //カメラの回転速度,プレイヤーの移動速度
    float speed = 0.0f;
	int walking = 1;
    int dash = 2;
    bool isHit;

	float jumpVelocity = 5.0f;
	float gravity = 0.01f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	std::string debugstr = "null";

	RayCastData downRay;
	RayCastData play;
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
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	// ステートマネージャーの更新
	pStateManager_->Update();


	//Y座標0から下に向かうレイ（坂を上るときに必要）
	downRay.start = {transform_.position_.x,0,transform_.position_.z};   //レイの発射位置
	downRay.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &downRay); //レイを発射

	//プレイヤーの頭から飛ばすレイ
	play.start = { transform_.position_.x,transform_.position_.y+0.3f,transform_.position_.z };   //レイの発射位置
	play.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &play); //レイを発射
	
	if (downRay.hit)
	{
		if (downRay.hit)
		{
			if (!isJumping_)
			{
				// ジャンプ
				if (Input::IsKeyDown(DIK_SPACE))
				{
					isJumping_ = true;
					moveY_ = 0.2f; // ジャンプ初速度を設定
				}
			}
			else
			{
				// 自由落下
				moveY_ -= 0.01f; // 重力を適用

				// 最大落下速度を制限
				if (moveY_ <= -0.25f)
				{
					moveY_ = -0.25f;
				}
			}

			// 地面との衝突を検出
			if (play.dist <= 0.25f && isJumping_)
			{
				moveY_ = 0.0f;
				isJumping_ = false;
			}

			// 地面にいる時の位置調整
			if (!isJumping_)
			{
				transform_.position_.y = -downRay.dist;
			}

			// Y座標の更新
			transform_.position_.y += moveY_;
		}

		// ステージ外に落ちてしまった場合のリセット
		if (transform_.position_.y <= -100)
		{
			transform_.position_ = { 0, -downRay.dist, 0 };
		}
	}

	/*
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
	*/

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

/*
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
	*/

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

	////くりっくしたら
	//if (Input::IsMouseButtonDown(0) && !(Input::IsMouseButton(1)))
	//{
	//	Attack* pAtk = Instantiate<Attack>(GetParent());
	//	//pAtk->SetMove(camTarget);
	//	//pAtk->SetPosition(camTarget);
	//	pAtk->SetTime(2);

	//}
	//else if (Input::IsMouseButtonDown(0) && (Input::IsMouseButton(1)) && jewelCount_ > 0)
	//{
	//	JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());
	//	// プレイヤーの回転行列を作成
	//	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	//		XMConvertToRadians(transform_.rotate_.y),
	//		XMConvertToRadians(transform_.rotate_.z));

	//	// プレイヤーの前方ベクトルを取得
	//	XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),playerRotMat);
	//	pJB->BulletDirection(playerForwardVector);
	//	pJB->BulletPosition(transform_.position_);
	//	pJB->BulletRotate(transform_.rotate_);
	//	jewelCount_--;
	//}

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
	//if (currentState_) {
	//	delete currentState_;
	//}
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
	if (attackCountDown <= 0)
	{
		attackCountDown = attackWaitTime;
		attackEnd = false;
	}
	else
	{
		attackCountDown--;
	}

	// 攻撃カウントダウンが特定の値以下で、Aimしておらず、攻撃が終了していない場合に攻撃を生成
	if (attackCountDown <= 8 && !InputManager::IsAim && !attackEnd)
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		// 攻撃の移動先と位置を設定（例: pAtk->SetMove(camTarget);）
		// pAtk->SetPosition(camTarget);
		pAtk->SetTime(4);
	}

	// 左クリックと右クリックが同時に押され、ジュエルが1つ以上ある場合にジュエルバレットを生成
	if (InputManager::IsAttack() && InputManager::IsAim() && jewelCount_ > 0)
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
