#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"

#include "Player.h"
#include "Stage.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title")
{
}

//初期化
void TitleScene::Initialize()
{
	Instantiate<Stage>(this);
}

//更新
void TitleScene::Update()
{
	static float wave = 0;
	XMVECTOR camera = { 0, 15, -25,0 };
	XMFLOAT3 camTar = { 0, 2, -5 };
	Camera::SetTarget(camTar);

	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	camera = XMVector3TransformCoord(camera, rotMatX * rotMatY);


	XMVECTOR RightMove = XMVectorSet(1, 0, 0, 0);
	RightMove = XMVector3TransformCoord(RightMove, rotMatY);
	
	camVec = XMLoadFloat3(&transform_.position_);
	camVec += RightMove;

	XMStoreFloat3(&transform_.position_, camVec);


	XMStoreFloat3(&pos, camVec + camera);

	Camera::SetPosition(pos);
	
	wave++;
}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}