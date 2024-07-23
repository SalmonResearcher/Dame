#include "TitleScene.h"
#include "Global.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Audio.h"

namespace {
	//���g��
	float Frequency = 0;
	//�傫�����ő�l�ɂȂ�܂ł̑��x
	float ScaleSpeed = 0.05f;
	//�ő�̑傫��
	float ScaleAmplitude = 0.05f;
	//�U�ꕝ���ő�ɂȂ�܂ł̑��x
	float SwaySpeed = 0.5f;
	float SwaySpeedHuman = 2.0f;
	//�U�ꕝ�̑傫��
	float SwayAmplitude = 0.05f;
}

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_{-1,-1,-1,-1,-1}
{
}

//������
void TitleScene::Initialize()
{
	hBGM_ = Audio::Load("SE/TitleScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, 0.15f);


	const char* ImageName[] = { "Title_BG.png","Title_Slime.png", "Title_Ground.png","Title_human.png","Title_Logo.png","PressKey.png"};
	for (int l = 0; l < MAX_IMAGE; l++)
	{
		//�摜��ǂݏo��
		hImage_[l] = Image::Load(ImageName[l]);
		assert(hImage_[l] >= 0);
	}
	Global::jewel = 0;
	Global::killcount = 0;
	Global::jewelKill = 0;

}

void TitleScene::Update()
{
		float scale = 1.0f + ScaleAmplitude * sin(Frequency);
		float scaleSlime = 1.0f+ScaleAmplitude * sin(Frequency*0.5);
		trImage_[1].scale_.x = scaleSlime;
		trImage_[1].scale_.y = scaleSlime;

		float swaySlime = SwayAmplitude * sin(Frequency * SwaySpeed);
		float swayHuman = SwayAmplitude * sin(Frequency * SwaySpeedHuman);
		trImage_[1].position_.x = swaySlime;

		trImage_[3].position_.y = swayHuman;
		trImage_[4].scale_.x = scale;
		trImage_[4].scale_.y = scale;

	Frequency += ScaleSpeed;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SELECT);
	}
}

//�`��
void TitleScene::Draw()
{
	for (int l = 0; l < MAX_IMAGE; l++) {
		Image::SetTransform(hImage_[l], trImage_[l]);
		Image::Draw(hImage_[l]);
	}
}

//�J��
void TitleScene::Release()
{
}