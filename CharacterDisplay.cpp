#include "CharacterDisplay.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"


//コンストラクタ
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),pText(nullptr)
{
}

//初期化
void CharacterDisplay::Initialize()
{
	pText = new Text;
	pText->Initialize();
}

//更新
void CharacterDisplay::Update()
{
	kill_ = ((Player*)FindObject("Player"))->GetKillCount();
	jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();

	score_ = (jewel_ * 200) + (kill_ * 25);
}

//描画
void CharacterDisplay::Draw()
{
	pText->Draw(30, 30, score_);
}

//開放
void CharacterDisplay::Release()
{
}