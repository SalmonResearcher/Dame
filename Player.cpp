#include "Player.h"
#include "Stage.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), dash(1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

}

void Player::Update()
{
	Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
	int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

	RayCastData data;
	data.start = {tPlayer_.position_.x,0,tPlayer_.position_.z};   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hGroundModel, &data); //レイを発射

	RayCastData player;
	player.start = tPlayer_.position_;   //レイの発射位置
	player.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hGroundModel, &player); //レイを発射

	moveY -= 0.01;

	//レイが当たったら
	if (data.hit && player.dist <= 0.5)
	{
		moveY = 0;
		tPlayer_.position_.y = -data.dist;
	}

	if (Input::IsKeyDown(DIK_SPACE))
		moveY = 0.5;

	tPlayer_.position_.y += moveY;

	if (Input::IsKey(DIK_LSHIFT))
		dash = 2;

	else
		dash = 1;

	//if (Input::IsKey(DIK_W))
	//{
	//	tPlayer_.position_.z += SPEED * dash;
	//}

	//if (Input::IsKey(DIK_S))
	//{
	//	tPlayer_.position_.z -= SPEED * dash;
	//}

	//if (Input::IsKey(DIK_A))
	//{

	//}

	static bool debug = true;
	//マウス位置固定
	if (Input::IsKeyDown(DIK_SPACE))
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

	if (debug)
		SetCursorPos(800, 400);


	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 camMove = { 0,0,0 };

	//マウスの移動量
	move.x += Input::GetMouseMove().x;
	move.y += Input::GetMouseMove().y;
	move.z += Input::GetMouseMove().z;	//マウスホイール

	//マウスの移動量に応じてカメラを回転させる
	camMove.y = move.x;
	camMove.x = move.y;

	//↓デバック用
	Debug::Log("camMove.y = ");
	Debug::Log(camMove.x, true);
	//↑デバッグ用

	//マウスセンシティビリティ
	camMove.x *= 0.1;
	camMove.y *= 0.1;

	//上を向きすぎないように
	if (camMove.x >= 69)
	{
		camMove.x = 69;
		move.y = 690;
	}

	//下を向きすぎない
	if (camMove.x <= -20)
	{
		camMove.x = -20;
		move.y = -200;
	}

	tCamera.rotate_ = camMove;

	//Y軸の回転行列
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(tCamera.rotate_.y));

	//X軸の回転軸
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(tCamera.rotate_.x));

	//移動ベクトル
	XMVECTOR nowVec = XMLoadFloat3(&tPlayer_.position_);			//今のカメラ位置座標
	XMVECTOR frontMove = XMVectorSet(0, 0, SPEED * dash, 0);		//z座標に動く速度
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y軸回転行列をfrontmoveベクトルへ変換

	//上下左右回転
	XMVECTOR upDownMove = XMVectorSet(0, SPEED * dash, 0, 0);
	upDownMove = XMVector3TransformCoord(upDownMove, rotMatY);
	XMVECTOR leftRightMove = XMVectorSet(SPEED * dash, 0, 0, 0);
	leftRightMove = XMVector3TransformCoord(leftRightMove, rotMatY);

	//プレイヤーもここで移動させる
	vecPlayer_ = XMLoadFloat3(&tPlayer_.position_);
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


	XMStoreFloat3(&tPlayer_.position_, vecPlayer_);

	//カメラ移動
	XMStoreFloat3(&tCamera.position_, nowVec);

	//カメラ本体
	XMVECTOR vCam = { 0,0,-10,0 };

	//カメラ注視点
	XMFLOAT3 camTarget = tPlayer_.position_;
	//camTarget.z += 2;
	Camera::SetTarget(camTarget);
	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//カメラ座標変更
	XMStoreFloat3(&Camposition_, nowVec + vCam);

	//カメラ移動
	Camera::SetPosition(Camposition_);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, tPlayer_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
