#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"),hImage_(0)
{
}

//������
void TitleScene::Initialize()
{
	hImage_ = Image::Load("TestTitle.png");
	assert(hImage_ <= 0);

	trPict_.scale_ = { 0.5,0.5,0.5 };
}

//�X�V
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager::ChangeScene(SCENE_ID_)
	}
}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hImage_, trPict_);
	Image::Draw(hImage_);
}

//�J��
void TitleScene::Release()
{
}