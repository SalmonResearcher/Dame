#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Global.h"
//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//������
void ResultScene::Initialize()
{
	pDisplay_ = Instantiate<CharacterDisplay>(this);

	score_ = Global::GetScore();

	pDisplay_->SetScorePosition(850, 5);
}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
	pDisplay_->DrawScore(score_);
}

//�J��
void ResultScene::Release()
{
}