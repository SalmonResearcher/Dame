#include "Score.h"
#include "Engine/Debug.h"
#include "Global.h"

#include "Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <sstream>
#include <iomanip>

#include <math.h>
#include <cstdio>

namespace
{
    int baseJewelScore;
    int baseKillScore;
    const int MAX_SCORE = 999999;
}
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
    baseJewelScore = Global::GetJewelScore();
    baseKillScore = Global::GetKillScore();

    // �\���X�R�Aup_�����X��score_�ɋ߂Â���
    if (curScore_ != score_) {
        int difference = score_ - up_;
        incrementValue_ = difference / incrementSteps_;
        //1f�O�̑����ꂽ�X�R�A
        curScore_ = score_;
    }

    // �\���X�R�Aup_��ڕW�X�R�A�ɋ߂Â���
    if (up_ != score_ && countUp_) {
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
    std::stringstream ss;
    ss << std::setw(6) << std::setfill('0') << up_;
    std::string result = ss.str();

    pText_->Draw(posX_, posY_, result.c_str(), true);
}


//�J��
void Score::Release()
{
}

void Score::ScoreCaluc()
{
    if (FindObject("Player") != nullptr) {
        kill_ = ((Player*)FindObject("Player"))->GetKillCount();
    }
    else {
        kill_ = Global::GetKillCount();
        jewel_ = Global::GetJewel();
        bulletScore_ = Global::GetJewelKill();
    }

    if (FindObject("JewelBox") != nullptr) {
        jewel_ = ((JewelBox*)FindObject("JewelBox"))->ReturnJewel();
        bulletScore_ = ((JewelBox*)FindObject("JewelBox"))->GetKillScore();
    }

    if (score_ >= MAX_SCORE)
    {
        score_ = MAX_SCORE;
    }
    else 
    {
        score_ = (jewel_ * baseJewelScore) + (kill_ * baseKillScore) + bulletScore_;
    }

}
