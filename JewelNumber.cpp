#include "JewelNumber.h"
#include "Engine/Debug.h"
#include "Global.h"

#include <sstream>
#include <iomanip>

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
    // 2桁で0埋めのフォーマット指定子を使用して文字列を生成
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << jewel_;
    std::string result = ss.str();

    pText_->Draw(posX_, posY_, result.c_str(), true);
}

//開放
void JewelNumber::Release()
{
}
