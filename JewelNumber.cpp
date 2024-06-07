#include "JewelNumber.h"
#include "Engine/Debug.h"
#include "Global.h"

#include "Player.h"



//コンストラクタ
JewelNumber::JewelNumber(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"),pText_(nullptr)
{
}

//初期化
void JewelNumber::Initialize()
{
    pText_ = new Text;
    pText_->Initialize("jewel_number.png", 50, 100, 10);
}

//更新
void JewelNumber::Update()
{
    if (FindObject("Player") != nullptr) {
        jewel_ = ((Player*)FindObject("Player"))->GetJewelCount();
    }
    if (jewel_ <= 0)
    {
        jewel_ = 0;
    }
}

//描画
void JewelNumber::Draw()
{
}

//描画
void JewelNumber::Draw(int _x, int _y)
{
    // 2桁で0埋めのフォーマット指定子を使用して文字列を生成
    char buffer[3]; // 文字列+1分の配列サイズ
    snprintf(buffer, sizeof(buffer), "%02d", jewel_);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(), true);
}

//開放
void JewelNumber::Release()
{
}