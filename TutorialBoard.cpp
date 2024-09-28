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

//コンストラクタ
TutorialBoard::TutorialBoard(GameObject* parent)
    :GameObject(parent, "TutorialBoard")
{
}

//デストラクタ
TutorialBoard::~TutorialBoard()
{
}

//初期化
void TutorialBoard::Initialize()
{
	for (int l = 0; l < B_MAX; l++)
	{
		number = std::to_string(l+1);

		name + number + ext;

		//Stage1、Stage2、Stage3を呼ぶ
		hBoard_[l] = Model::Load(name + number + ext);
		assert(hBoard_[l] >= 0);

		trBoard_[l].position_.y = stageZelo;
		trBoard_[l].position_.x = stageZelo;
		trBoard_[l].position_.z = bMove;

		bMove += boardInterval;
	}

	pCam = static_cast<PlayerCamera*>(FindObject("PlayerCamera"));
}

//更新
void TutorialBoard::Update()
{
	//カメラ回転行列
	XMFLOAT4X4 cameraRot = pCam->GetCameraRotateMatrix();

	//カメラの水平回転角度を計算
	float CameraYaw = atan2f(-cameraRot._13, cameraRot._11);

	//カメラの向きの逆方向にする
	CameraYaw += XM_PI;

	for (int l = 0; l < B_MAX; l++)
	{

		// プレイヤーの回転を更新
		trBoard_[l].rotate_.y = XMConvertToDegrees(CameraYaw);
	}
}

//描画
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

//開放
void TutorialBoard::Release()
{
	bMove = 0;
}