#include "JewelNumber.h"
#include "Engine/Debug.h"
#include "Global.h"

#include <sstream>
#include <iomanip>

#include "Player.h"



//�R���X�g���N�^
JewelNumber::JewelNumber(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"),pText_(nullptr)
{
}

//������
void JewelNumber::Initialize()
{
    pText_ = new Text;
    pText_->Initialize("jewel_number.png", 50, 100, 10);
}

//�X�V
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


//�`��
void JewelNumber::Draw()
{
    // 2����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << jewel_;
    std::string result = ss.str();

    pText_->Draw(posX_, posY_, result.c_str(), true);
}

//�J��
void JewelNumber::Release()
{
}
