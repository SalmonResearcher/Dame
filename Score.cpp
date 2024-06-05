#include "Score.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//コンストラクタ
Score::Score(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"), pText(nullptr)
{
}

//初期化
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize("score_number.png", 50, 256, 10);
}

//更新
void Score::Update()
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
void Score::Draw()
{
}

//描画
void Score::Draw(int _x,int _y)
{
    pText->Draw(_x, _y, up_);
}

//開放
void Score::Release()
{
}