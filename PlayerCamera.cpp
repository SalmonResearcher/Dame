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
    // �}�E�X���x�̒���
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

    // �}�E�X�̈ړ��ʂ̌v�Z
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    move.x += mouseMove.x * mouseSens;
    move.y += mouseMove.y * mouseSens;
    move.z += mouseMove.z * mouseSens; // �}�E�X�z�C�[��

    // �}�E�X�̈ړ��ʂɊ�Â��J������]
    camMove.y = move.x;
    camMove.x = move.y;

    // �J�����̉�]�ʂ̃X�P�[�����O
    camMove.x *= CAM_MOVE_SCALE;
    camMove.y *= CAM_MOVE_SCALE;

    // �J�����̌�������
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

    // �J�����̉�]��K�p
    transform_.rotate_ = camMove;

    // �v���C���[�̈ʒu�x�N�g�����擾
    SetMoveVector(pPlayer_->GetPlayerPosition());

    // �J�����̈ʒu���v���C���[�̈ʒu�ɐݒ�
    XMStoreFloat3(&transform_.position_, moveVec_);

    // �J�����{�̂̈ʒu
    XMVECTOR vCam = XMVectorSet(0, 3, -15, 0);

    // �J�����̒����_���v���C���[�ɐݒ�
    XMFLOAT3 camTarget = pPlayer_->GetPlayerPosition();
    Camera::SetTarget(camTarget);

    // �J�����̉�]�s���K�p
    vCam = XMVector3TransformCoord(vCam, GetRotateX() * GetRotateY());

    // �J�������W�̍X�V
    XMStoreFloat3(&transform_.position_, moveVec_ + vCam);

    // �J�����̈ʒu��ݒ�
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