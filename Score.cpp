#include "Score.h"
#include "Engine/Debug.h"
#include "Global.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>
#include <cstdio>


//コンストラクタ
Score::Score(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"), pText_(nullptr)
{
}

//初期化
void Score::Initialize()
{
    pText_ = new Text;
    pText_->Initialize("score_number.png", 50,100, 10);
}

//更新
void Score::Update()
{
    //1f前の足されたスコア
    int curScore_ = score_;
    if (FindObject("Player") != nullptr) {
        kill_ = ((Player*)FindObject("Player"))->GetKillCount();
    }

    if (FindObject("JewelBox") != nullptr) {
        jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();
        bulletScore_ = ((JewelBox*)FindObject("JewelBox"))->GetKillScore();
    }

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
    saveScore_ = up_;
    Global::SetScore(saveScore_);

}

//描画
void Score::Draw()
{
}

//描画
void Score::Draw(int _x, int _y)
{
    // 6桁で0埋めのフォーマット指定子を使用して文字列を生成
    char buffer[7]; // 文字列+1分の配列サイズ
    snprintf(buffer, sizeof(buffer), "%06d", up_);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(),true);
}

//描画
void Score::Draw(int _x, int _y ,int num)
{
    // 6桁で0埋めのフォーマット指定子を使用して文字列を生成
    char buffer[7]; // 文字列+1分の配列サイズ
    snprintf(buffer, sizeof(buffer), "%06d", num);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(), true);
}

//開放
void Score::Release()
{
}