#include "TutorialBoard.h"
#include "Engine/Model.h"

#include "PlayerCamera.h"

namespace
{
	float bMove = 0.0f;
	float boardInterval = 10;
	float stageZelo = -5;
	PlayerCamera* pCam;
}

//�R���X�g���N�^
TutorialBoard::TutorialBoard(GameObject* parent)
    :GameObject(parent, "TutorialBoard")
{
}

//�f�X�g���N�^
TutorialBoard::~TutorialBoard()
{
}

//������
void TutorialBoard::Initialize()
{
	for (int l = 0; l < B_MAX; l++)
	{
		number = std::to_string(l+1);

		name + number + ext;

		//Stage1�AStage2�AStage3���Ă�
		hBoard_[l] = Model::Load(name + number + ext);
		assert(hBoard_[l] >= 0);

		trBoard_[l].position_.y = stageZelo;
		trBoard_[l].position_.x = stageZelo;
		trBoard_[l].position_.z = bMove;

		bMove += boardInterval;
	}

	pCam = static_cast<PlayerCamera*>(FindObject("PlayerCamera"));
}

//�X�V
void TutorialBoard::Update()
{
	//�J������]�s��
	XMFLOAT4X4 cameraRot = pCam->GetCameraRotateMatrix();

	//�J�����̐�����]�p�x���v�Z
	float CameraYaw = atan2f(-cameraRot._13, cameraRot._11);

	//�J�����̌����̋t�����ɂ���
	CameraYaw += XM_PI;

	for (int l = 0; l < B_MAX; l++)
	{

		// �v���C���[�̉�]���X�V
		trBoard_[l].rotate_.y = XMConvertToDegrees(CameraYaw);
	}
}

//�`��
void TutorialBoard::Draw()
{
	for (int i = 0; i < B_MAX; i++)
	{
		Model::SetTransform(hBoard_[i], trBoard_[i]);
	}

	for (int l = 0; l < B_MAX; l++)
	{
		Model::Draw(hBoard_[l]);
	}
}

//�J��
void TutorialBoard::Release()
{
	bMove = 0;
}