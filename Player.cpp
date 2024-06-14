#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "math.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"

#include "Engine/SceneManager.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), dash_(1),jewelCount_(0), weight_(1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	BoxCollider* collider = new BoxCollider({0,0.5,0},{1.0,1.0,1.0});
	AddCollider(collider);

}

void Player::Update()
{

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = {tPlayer_.position_.x,0,tPlayer_.position_.z};   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	RayCastData play;
	play.start = { tPlayer_.position_.x,tPlayer_.position_.y+0.3f,tPlayer_.position_.z };   //レイの発射位置
	play.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &play); //レイを発射
	
	if (data.hit)
	{
		//ジャンプ
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping)
		{
			isJumping = true;
			moveY += 0.2f * weight_;
		}
		
		else if (isJumping)
		{
			//自由落下
			moveY -= 0.01;

			if (moveY <= -0.25f)
			{
				moveY = -0.25f;
			}
		}

		if (play.dist <= 0.25 && isJumping)
		{
			moveY = 0.0f;
			isJumping = false;
		}

		if (!isJumping)
		{
			tPlayer_.position_.y = -data.dist;
		}

		tPlayer_.position_.y += moveY;
	}



	if (Input::IsKey(DIK_LSHIFT))
		dash_ = 2;

	else
		dash_ = 1;

	static bool debug = true;


	if (Input::IsKeyDown(DIK_RSHIFT))
	{
		if (debug)
		{
			debug = false;
		}
		else
		{
			debug = true;
		}
	}

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

	//Y軸の回転行列
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(tCamera.rotate_.y));

	//X軸の回転軸
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(tCamera.rotate_.x));

	//移動ベクトル
	XMVECTOR nowVec = XMLoadFloat3(& tPlayer_.position_);			//今のカメラ位置座標
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash_ * weight_, 0);		//z座標に動く速度
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y軸回転行列をfrontmoveベクトルへ変換

	//左右
	XMVECTOR sideVec_ = XMVectorSet(speed_ * dash_ * weight_, 0, 0, 0);
	sideVec_ = XMVector3TransformCoord(sideVec_, rotMatY);

	//プレイヤーもここで移動させる
	vecPlayer_ = XMLoadFloat3(&tPlayer_.position_);

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
	XMStoreFloat3(&tPlayer_.position_, vecPlayer_);

	


	//カメラ移動
	XMStoreFloat3(&tCamera.position_, nowVec);

	//カメラ本体
	XMVECTOR vCam = { 0,2,-10,0 };

	//カメラ注視点
	XMFLOAT3 camTarget = tPlayer_.position_;

	Camera::SetTarget(camTarget);

	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//カメラ座標変更
	XMStoreFloat3(&Camposition_, nowVec + vCam);
	
	//カメラ移動
	Camera::SetPosition(Camposition_);

	transform_ = tPlayer_;

	// カメラの回転行列を作成
	XMMATRIX cameraRotMat = rotMatX * rotMatY;

	// カメラの回転行列を抽出
	XMFLOAT4X4 cameraRot;

	//XMFloat4*4に格納
	XMStoreFloat4x4(&cameraRot, cameraRotMat);

	//プレイヤーの水平方向の角度を求める
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	//// プレイヤーの回転を更新
	tPlayer_.rotate_.y = XMConvertToDegrees(playerYaw);

	// プレイヤーの回転行列を作成
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(tPlayer_.rotate_.x),
		XMConvertToRadians(tPlayer_.rotate_.y),
		XMConvertToRadians(tPlayer_.rotate_.z));

	// プレイヤーの前方ベクトルを取得
	XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);


	//くりっくしたら
	if (Input::IsMouseButtonDown(0) && !(Input::IsMouseButton(1)))
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		pAtk->SetMove(camTarget);
		pAtk->SetPosition(camTarget);
		pAtk->SetTime(2);

	}
	else if (Input::IsMouseButtonDown(0) && (Input::IsMouseButton(1)) && jewelCount_ > 0)
	{
		JewelBullet* pJB = Instantiate<JewelBullet>(GetParent());
		// プレイヤーの回転行列を作成
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(tPlayer_.rotate_.x),
			XMConvertToRadians(tPlayer_.rotate_.y),
			XMConvertToRadians(tPlayer_.rotate_.z));

		// プレイヤーの前方ベクトルを取得
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),playerRotMat);
		pJB->BulletDirection(playerForwardVector);
		pJB->BulletPosition(tPlayer_.position_);
		pJB->BulletRotate(tPlayer_.rotate_);
		jewelCount_--;
	}

	//too heavy, more heavy
	weight_ = 1 - min(0.99, jewelCount_ * JEWEL_WEIGHT);

	transform_ = tPlayer_;
	transform_.rotate_ = tPlayer_.rotate_;
}



void Player::Draw()
{
	Model::SetTransform(hModel_, tPlayer_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::StageRay()
{
	if ((Stage*)FindObject("Stage") != nullptr)
	{
		hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();
		RayCastData down;
	}
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

}
