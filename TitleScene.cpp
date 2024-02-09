#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"),hImage_(0),wave(0)
{
}

//初期化
void TitleScene::Initialize()
{
	hImage_ = Image::Load("TestTitle.png");
	assert(hImage_ <= 0);

	trPict_.scale_ = { 0.5,0.5,0.5 };
}

//更新
void TitleScene::Update()
{
	if (wave >= 3)
	{
		wave = 0;
	}
	float moveY = (float)sin(wave) / 5;
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}

	wave += 0.02;
	trPict_.scale_ = {moveY,moveY,moveY};
	Debug::Log("wave = ");
	Debug::Log(wave, true);
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hImage_, trPict_);
	Image::Draw(hImage_);
}

//開放
void TitleScene::Release()
{
}