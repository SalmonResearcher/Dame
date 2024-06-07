#include "JewelNumber.h"
#include "Engine/Debug.h"
#include "Global.h"

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
}

//�`��
void JewelNumber::Draw(int _x, int _y)
{
    // 2����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
    char buffer[3]; // ������+1���̔z��T�C�Y
    snprintf(buffer, sizeof(buffer), "%02d", jewel_);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(), true);
}

//�J��
void JewelNumber::Release()
{
}