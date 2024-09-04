#include "PlayerCamera.h"
#include "Player.h"

#include "Engine/Camera.h"
#include "Engine/Input.h"

#include <algorithm>

namespace {
	float mouseSens = 1;
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
    // マウス感度の調整
    if (Input::IsKeyDown(DIK_UP))
    {
        mouseSens += Input::IsKey(DIK_LSHIFT) ? MOUSE_SENSITIVITY_INCREMENT_FAST : MOUSE_SENSITIVITY_INCREMENT_NORMAL;
        mouseSens = Clamp(mouseSens, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX);
    }

    if (Input::IsKeyDown(DIK_DOWN))
    {
        mouseSens -= Input::IsKey(DIK_LSHIFT) ? MOUSE_SENSITIVITY_INCREMENT_FAST : MOUSE_SENSITIVITY_INCREMENT_NORMAL;
        mouseSens = Clamp(mouseSens, MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX);
    }

    static XMFLOAT3 move = { 0, 0, 0 };
    static XMFLOAT3 camMove = { 0, 0, 0 };

    // マウスの移動量の計算
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    move.x += mouseMove.x * mouseSens;
    move.y += mouseMove.y * mouseSens;
    move.z += mouseMove.z * mouseSens; // マウスホイール

    // マウスの移動量に基づくカメラ回転
    camMove.y = move.x;
    camMove.x = move.y;

    // カメラの回転量のスケーリング
    camMove.x *= CAM_MOVE_SCALE;
    camMove.y *= CAM_MOVE_SCALE;

    // カメラの向き制限
    if (camMove.x >= MAX_LOOK_UP)
    {
        camMove.x = MAX_LOOK_UP;
        move.y = MAX_LOOK_UP*10;
    }
    else if (camMove.x <= MIN_LOOK_DOWN)
    {
        camMove.x = MIN_LOOK_DOWN;
        move.y = MIN_LOOK_DOWN*10;
    }

    // カメラの回転を適用
    transform_.rotate_ = camMove;

    // プレイヤーの位置ベクトルを取得
    SetMoveVector(pPlayer_->GetPlayerPosition());

    // カメラの位置をプレイヤーの位置に設定
    XMStoreFloat3(&transform_.position_, moveVec_);

    // カメラ本体の位置
    XMVECTOR vCam = XMVectorSet(0, 3, -15, 0);

    // カメラの注視点をプレイヤーに設定
    XMFLOAT3 camTarget = pPlayer_->GetPlayerPosition();
    Camera::SetTarget(camTarget);

    // カメラの回転行列を適用
    vCam = XMVector3TransformCoord(vCam, GetRotateX() * GetRotateY());

    // カメラ座標の更新
    XMStoreFloat3(&transform_.position_, moveVec_ + vCam);

    // カメラの位置を設定
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

float PlayerCamera::Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}