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
	//�}�E�X���x
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

	//�}�E�X�ʒu�Œ�
	if (debug)
		SetCursorPos(800, 400);

	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 camMove = { 0,0,0 };

	//�}�E�X�̈ړ���
	move.x += Input::GetMouseMove().x * mouseSens;
	move.y += Input::GetMouseMove().y * mouseSens;
	move.z += Input::GetMouseMove().z * mouseSens;	//�}�E�X�z�C�[��

	//�}�E�X�̈ړ��ʂɉ����ăJ��������]������
	camMove.y = move.x;
	camMove.x = move.y;

	//�}�E�X�Z���V�e�B�r���e�B
	camMove.x *= 0.1;
	camMove.y *= 0.1;

	//�������������Ȃ��悤��
	if (camMove.x >= 75)
	{
		camMove.x = 75;
		move.y = 750;
	}

	//������������Ȃ�
	if (camMove.x <= -85)
	{
		camMove.x = -85;
		move.y = -850;
	}
	//�J������Y���ŉ�]
	transform_.rotate_ = camMove;
	
	//�v���C���[�̈ʒu�x�N�g���i�J�����̒����_�j�����
	SetMoveVector(pPlayer_->GetPlayerPosition());

	//�J�����̈ʒu���v���C���[�̈ʒu�x�N�g��
	XMStoreFloat3(&transform_.position_,moveVec_);

	//�J�����{��
	XMVECTOR vCam = { 0,2,-10,0 };

	//�J���������_�̓v���C���[
	XMFLOAT3 camTarget = pPlayer_->GetPlayerPosition();

	Camera::SetTarget(camTarget);

	//�J�����ɉ�]�s���K�p
	vCam = XMVector3TransformCoord(vCam, GetRotateX() * GetRotateY());

	//�J�������W�X�V
	XMStoreFloat3(&transform_.position_, moveVec_ + vCam);

	//�J�������ړ�
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
