#include "TitleScene.h"
#include "Global.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Audio.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_{-1,-1,-1,-1,-1},frequency_(0)
{
}

//初期化
void TitleScene::Initialize()
{
	hBGM_ = Audio::Load("Sounds/BGM/TitleScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, Global::MUSIC_VOLUME);


	const char* ImageName[] = { "Title_BG.png","Title_Slime.png", "Title_Ground.png","Title_human.png","Title_Logo.png","PressKey.png"};
	for (int l = 0; l < MAX_IMAGE; l++)
	{
		//画像を読み出す
		hImage_[l] = Image::Load(ImageName[l]);
		assert(hImage_[l] >= 0);
	}

	Global::jewel = 0;
	Global::killcount = 0;
	Global::jewelKill = 0;

}

void TitleScene::Update()
{
		float scale = 1.0f + SCALE_SPEED * sin(frequency_);
		float scaleSlime = 1.0f+SCALE_SPEED * sin(frequency_*0.5);
		trImage_[SLIME].scale_.x = scaleSlime;
		trImage_[SLIME].scale_.y = scaleSlime;

		float swaySlime = SWAY_AMPLITUDE * sin(frequency_ * SWAY_SPEED);
		float swayHuman = SWAY_AMPLITUDE * sin(frequency_ * HUMAN_SWAY_SPEED);
		trImage_[SLIME].position_.x = swaySlime;

		trImage_[HUMAN].position_.y = swayHuman;
		trImage_[LOGO].scale_.x = scale;
		trImage_[LOGO].scale_.y = scale;

	frequency_ += SCALE_SPEED;

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