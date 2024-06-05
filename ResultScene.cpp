#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//������
void ResultScene::Initialize()
{
	pDisp_ = Instantiate<CharacterDisplay>(this);
	pDisp_->ScorePosition(40, 40, score);

	pDisp_->TimerPosition(0, 0, false);
}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
	
}

//�J��
void ResultScene::Release()
{
}