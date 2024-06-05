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
	: GameObject(parent, "CharacterDisplay"),pText_(nullptr)
{
}

//初期化
void CharacterDisplay::Initialize()
{
	pText_ = new Text;
	pText_->Initialize("score_number.png", 50, 256, 10);
	pScore_ = Instantiate<Score>(this);
}

//更新
void CharacterDisplay::Update()
{
}

//描画
void CharacterDisplay::Draw()
{
	pScore_->Draw(950,15);
}

//開放
void CharacterDisplay::Release()
{
}