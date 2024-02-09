#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"),hImage_(0)
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
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager::ChangeScene(SCENE_ID_)
	}
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