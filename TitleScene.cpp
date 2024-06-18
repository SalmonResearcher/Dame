#include "TitleScene.h"

#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "Title"),hImage_(0),wave(0)
{
}

//������
void TitleScene::Initialize()
{
	hImage_ = Image::Load("kansei.png");
	assert(hImage_ <= 0);
}

//�X�V
void TitleScene::Update()
{
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