#include "CharacterDisplay.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"


//�R���X�g���N�^
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),pText(nullptr)
{
}

//������
void CharacterDisplay::Initialize()
{
	pText = new Text;
	pText->Initialize();
}

//�X�V
void CharacterDisplay::Update()
{
	kill_ = ((Player*)FindObject("Player"))->GetKillCount();
	jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();

	score_ = (jewel_ * 200) + (kill_ * 25);
}

//�`��
void CharacterDisplay::Draw()
{
	pText->Draw(30, 30, score_);
}

//�J��
void CharacterDisplay::Release()
{
}