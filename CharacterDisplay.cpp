#include "CharacterDisplay.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//�R���X�g���N�^
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),pText(nullptr)
{
}

//������
void CharacterDisplay::Initialize()
{
	pText = new Text;
	pText->Initialize();
}

//�X�V
void CharacterDisplay::Update()
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
void CharacterDisplay::Draw()
{
	pText->Draw(30, 30, up_);
}

//�J��
void CharacterDisplay::Release()
{
}