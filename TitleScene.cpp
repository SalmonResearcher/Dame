#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace {
	float Frequency = 0;
	float ScaleSpeed = 0.05f;
	float ScaleAmplitude = 0.05f;
	float SwaySpeed = 0.05f;
	float SwayAmplitude = 0.05f;
}

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_{-1,-1,-1,-1,-1}
{
}

//初期化
void TitleScene::Initialize()
{
	const char* ImageName[] = { "Title_BG.png","Title_Slime.png", "Title_Ground.png","Title_human.png","Title_Logo.png"};
	for (int l = 0; l < MAX_IMAGE; l++)
	{
		//画像を読み出す
		hImage_[l] = Image::Load(ImageName[l]);
		assert(hImage_[l] >= 0);
	}
}

void TitleScene::Update()
{
		float scale = 1.0f + ScaleAmplitude * sin(Frequency);
		trImage_[1].scale_.x = scale;
		trImage_[1].scale_.y = scale;

		float sway = SwayAmplitude * sin(Frequency * SwaySpeed);
		trImage_[1].position_.x = sway;

	Frequency += ScaleSpeed;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}

//描画
void TitleScene::Draw()
{
	for (int l = 0; l < MAX_IMAGE; l++) {
		Image::SetTransform(hImage_[l], trImage_[l]);
		Image::Draw(hImage_[l]);
	}
}

//開放
void TitleScene::Release()
{
}