#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace {
	float wave = 0;
	float moveX = 0;
	
}

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_{-1,-1,-1,-1,-1}
{
}

//������
void TitleScene::Initialize()
{
	const char* ImageName[] = { "Title_BG.png","Title_Slime.png", "Title_Ground.png","Title_human.png","Title_Logo.png"};
	for (int l = 0; l < MAX_IMAGE; l++)
	{
		//�摜��ǂݏo��
		hImage_[l] = Image::Load(ImageName[l]);
		assert(hImage_[l] >= 0);
	}
}

//�X�V
void TitleScene::Update()
{

	moveX = (float)sin(wave)/1;

	trImage_[1].scale_.x += moveX;
	wave += 0.02;
	
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