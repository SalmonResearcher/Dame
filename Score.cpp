#include "Score.h"
#include "Engine/Debug.h"
#include "Global.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>
#include <cstdio>


//�R���X�g���N�^
Score::Score(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"), pText_(nullptr)
{
}

//������
void Score::Initialize()
{
    pText_ = new Text;
    pText_->Initialize("score_number.png", 50,100, 10);
}

//�X�V
void Score::Update()
{
    //1f�O�̑����ꂽ�X�R�A
    int curScore_ = score_;
    if (FindObject("Player") != nullptr) {
        kill_ = ((Player*)FindObject("Player"))->GetKillCount();
    }

    if (FindObject("JewelBox") != nullptr) {
        jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();
        bulletScore_ = ((JewelBox*)FindObject("JewelBox"))->GetKillScore();
    }

    score_ = (jewel_ * 200) + (kill_ * 25) + bulletScore_;
    // �\���X�R�Aup_�����X��score_�ɋ߂Â���
    if (curScore_ != score_) {
        int difference = score_ - up_;
        incrementValue_ = difference / incrementSteps_;
    }

    // �\���X�R�Aup_��ڕW�X�R�A�ɋ߂Â���
    if (up_ != score_) {
        // ����incrementValue_�����Ȃ璼�ږڕW�X�R�A�ɂ���
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

//�`��
void Score::Draw()
{
}

//�`��
void Score::Draw(int _x, int _y)
{
    // 6����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
    char buffer[7]; // ������+1���̔z��T�C�Y
    snprintf(buffer, sizeof(buffer), "%06d", up_);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(),true);
}

//�`��
void Score::Draw(int _x, int _y ,int num)
{
    // 6����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
    char buffer[7]; // ������+1���̔z��T�C�Y
    snprintf(buffer, sizeof(buffer), "%06d", num);
    std::string result = buffer;

    pText_->Draw(_x, _y, result.c_str(), true);
}

//�J��
void Score::Release()
{
}