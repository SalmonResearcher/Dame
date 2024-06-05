#include "CharacterDisplay.h"
#include "Score.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//コンストラクタ
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),pText(nullptr)
{
}

//初期化
void CharacterDisplay::Initialize()
{
	pText = new Text;
	pText->Initialize("score_number.png", 50, 256, 10);
	pScore = Instantiate<Score>(this);
}

//更新
void CharacterDisplay::Update()
{
}

//描画
void CharacterDisplay::Draw()
{
	pScore->Draw(900,15);
}

//開放
void CharacterDisplay::Release()
{
}