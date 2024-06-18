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
	hImage_ = Image::Load("kansei.png");
	assert(hImage_ <= 0);
}

//更新
void TitleScene::Update()
{
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