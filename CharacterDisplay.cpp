#include "CharacterDisplay.h"
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
	pText->Initialize();
}

//更新
void CharacterDisplay::Update()
{
	//1f前の足されたスコア
	int curScore_ = score_;
	kill_ = ((Player*)FindObject("Player"))->GetKillCount();
	jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();
	bulletScore_ = ((JewelBox*)FindObject("JewelBox"))->GetKillScore();

	score_ = (jewel_ * 200) + (kill_ * 25) + bulletScore_;
    // 表示スコアup_を徐々にscore_に近づける
    if (curScore_ != score_) {
        int difference = score_ - up_;
        incrementValue_ = difference / incrementSteps_;
    }

    // 表示スコアup_を目標スコアに近づける
    if (up_ != score_) {
        // 差がincrementValue_未満なら直接目標スコアにする
        if (std::abs(score_ - up_) < std::abs(incrementValue_)) {
            up_ = score_;
        }
        else {
            up_ += incrementValue_;
        }
    }
}

//描画
void CharacterDisplay::Draw()
{
	pText->Draw(30, 30, up_);
}

//開放
void CharacterDisplay::Release()
{
}