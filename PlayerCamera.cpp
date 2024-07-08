#include "PlayerCamera.h"
#include "Player.h"

#include "Engine/Camera.h"

#include "Engine/Input.h"

namespace {
	float mouseSens = 1;
	bool debug = true;
}


PlayerCamera::PlayerCamera(GameObject* parent) :GameObject(parent, "PlayerCamera"),pPlayer_(nullptr)
{
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Initialize()
{
	pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

void PlayerCamera::Update()
{
	//マウス感度
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

	if (Input::IsKeyDown(DIK_RSHIFT))
	{
		if (debug)
		{
			debug = false;
		} else {
			debug = true;
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
	//カメラをY軸で回転
	transform_.rotate_ = camMove;
	
	//プレイヤーの位置ベクトル（カメラの注視点）を取る
	SetMoveVector(pPlayer_->GetPlayerPosition());

	//カメラの位置≒プレイヤーの位置ベクトル
	XMStoreFloat3(&transform_.position_,moveVec_);

	//カメラ本体
	XMVECTOR vCam = { 0,2,-10,0 };

	//カメラ注視点はプレイヤー
	XMFLOAT3 camTarget = pPlayer_->GetPlayerPosition();

	Camera::SetTarget(camTarget);

	//カメラに回転行列を適用
	vCam = XMVector3TransformCoord(vCam, GetRotateX() * GetRotateY());

	//カメラ座標更新
	XMStoreFloat3(&transform_.position_, moveVec_ + vCam);

	//カメラを移動
	Camera::SetPosition(transform_.position_);

}

void PlayerCamera::Draw()
{
}

void PlayerCamera::Release()
{
}

void PlayerCamera::OnCollision(GameObject* pTarget)
{
}

XMFLOAT4X4 PlayerCamera::GetCameraRotateMatrix()
{
	XMFLOAT4X4 cameraRotate;
	XMStoreFloat4x4(&cameraRotate, GetRotateX() * GetRotateY());
	return cameraRotate;
}
