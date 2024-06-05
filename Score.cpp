#include "Score.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//�R���X�g���N�^
Score::Score(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"), pText(nullptr)
{
}

//������
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize("score_number.png", 50, 256, 10);
}

//�X�V
void Score::Update()
{
    //1f�O�̑����ꂽ�X�R�A
    int curScore_ = score_;
    kill_ = ((Player*)FindObject("Player"))->GetKillCount();
    jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();
    bulletScore_ = ((JewelBox*)FindObject("JewelBox"))->GetKillScore();

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
}

//�`��
void Score::Draw()
{
}

//�`��
void Score::Draw(int _x,int _y)
{
    pText->Draw(_x, _y, up_);
}

//�J��
void Score::Release()
{
}