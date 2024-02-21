#include "Player.h"
#include "Attack.h"
#include "Enemy.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), dash(1)
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
			moveY += 0.2f;
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
		dash = 2;

	else
		dash = 1;

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
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash, 0);		//z座標に動く速度
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y軸回転行列をfrontmoveベクトルへ変換

	//上下左右回転
	XMVECTOR upDownMove = XMVectorSet(0, speed_ * dash, 0, 0);
	upDownMove = XMVector3TransformCoord(upDownMove, rotMatY);
	XMVECTOR leftRightMove = XMVectorSet(speed_ * dash, 0, 0, 0);
	leftRightMove = XMVector3TransformCoord(leftRightMove, rotMatY);

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
		vecPlayer_ -= leftRightMove;
	}

	if (Input::IsKey(DIK_D))
	{
		vecPlayer_ += leftRightMove;
	}

	XMStoreFloat3(&movePlayer, vecPlayer_);

	XMStoreFloat3(&tPlayer_.position_, vecPlayer_);


	//カメラ移動
	XMStoreFloat3(&tCamera.position_, nowVec);

	//カメラ本体
	XMVECTOR vCam = { 0,2,-10,0 };

	//カメラ注視点
	XMFLOAT3 camTarget = tPlayer_.position_;

	//1F前の高さ
	static 	XMFLOAT3 prevPos = tPlayer_.position_;

	smoothCam.x = camTarget.x;
	smoothCam.y = camTarget.y - (camTarget.y - prevPos.y) / 2;
	smoothCam.z = camTarget.z;

	if (smoothCam.x < 0.01f)
		smoothCam.x = camTarget.x;

	if ((camTarget.y - prevPos.y) / 2 < 0.01f)
		smoothCam.y = camTarget.y;

	if (smoothCam.z < 0.01f)
		smoothCam.z = camTarget.z;

	prevPos.y = smoothCam.y;

	//Debug::Log("prev.y = ");
	//Debug::Log(prevPos.y, true);
	//Debug::Log("now.y = ");
	//Debug::Log(camTarget.y, true);
	Camera::SetTarget(smoothCam);

	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);


	//カメラ座標変更
	XMStoreFloat3(&Camposition_, nowVec + vCam);

	//Debug::Log(Camposition_.x, true);
	//Debug::Log(Camposition_.y, true);
	//Debug::Log(Camposition_.z,true);


	RayCastData cam;
	cam.start = camTarget;  //レイの発射位置
	cam.dir = Camposition_;       //レイの方向
	Model::RayCast(hStage_, &cam); //レイを発射



	//カメラ移動
	Camera::SetPosition(Camposition_);

	transform_ = tPlayer_;

	// カメラの回転行列を作成
	XMMATRIX cameraRotMat = rotMatX * rotMatY;

	// カメラの回転行列を抽出
	XMFLOAT4X4 cameraRot;
	XMStoreFloat4x4(&cameraRot, cameraRotMat);

	// カメラの向きにプレイヤーを向けるための回転角度を求める
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	// プレイヤーの回転を更新
	tPlayer_.rotate_.y = XMConvertToDegrees(playerYaw);

	//playerYawの+-1.5がちょうど右横から左横って感じ
	//Debug::Log(playerYaw);

	attackStart = playerYaw + 1.5;
	attackEnd = playerYaw - 1.5;

	Debug::Log("x = ");
	Debug::Log(tPlayer_.rotate_.x, true);

	Debug::Log("y = ");
	Debug::Log(tPlayer_.rotate_.y, true);

	Debug::Log("z = ");
	Debug::Log(tPlayer_.rotate_.z, true);

	if (Input::IsKeyDown(DIK_E))
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		pAtk->SetMove(camTarget);
		pAtk->SetPosition(camTarget);
	}

	if (Input::IsMouseButtonDown(0))
	{
		if ((Enemy*)FindObject("Enemy") != nullptr)
		{
			hEnemy_ = ((Enemy*)FindObject("Enemy"))->GetModelHandle();

			RayCastData attack;
			attack.start = { tPlayer_.position_ };   //レイの発射位置
			attack.dir = XMFLOAT3{ 0,0.5f,1 };       //レイの方向
			Model::RayCast(hEnemy_, &attack); //レイを発射

			if (/*attack.dist <= 2.0f &&*/ attack.hit)
			{
				((Enemy*)FindObject("Enemy"))->KillMe();
			}

		}


		}

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
