#include "CharacterDisplay.h"
#include "Score.h"
#include "Timer.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//�R���X�g���N�^
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),
	pText_(nullptr),scoreX_(950),scoreY_(5),timerX_(800),timerY_(5),showScore_(false),showTimer_(false)
{
}

//������
void CharacterDisplay::Initialize()
{
	pText_ = new Text;
	pText_->Initialize("score_number.png", 50, 256, 10);
	pScore_ = Instantiate<Score>(this);
	pTimer_ = Instantiate<Timer>(this);

	pTimer_->SetLimit(30);
	pTimer_->Start();

}

//�X�V
void CharacterDisplay::Update()
{
}

//�`��
void CharacterDisplay::Draw()
{
	if (showScore_) {
		// 6����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
		char buffer[7]; // ������+1���̔z��T�C�Y
		snprintf(buffer, sizeof(buffer), "%06d", score_);
		std::string result = buffer;

		pText_->Draw(scoreX_, scoreY_, result.c_str(), true);
	}
	if (showTimer_) {

	}
}

void CharacterDisplay::DrawScore(int _score)
{
	score_ = _score;
	pScore_->Draw(scoreX_, scoreY_, score_);
}

void CharacterDisplay::DrawScore()
{
	score_ = pScore_->GetScore();
	pScore_->Draw(scoreX_, scoreY_, score_);
}


void CharacterDisplay::DrawTimer()
{
	pTimer_->Draw(timerX_, timerY_);
}



//�J��
void CharacterDisplay::Release()
{
}


void CharacterDisplay::SetScorePosition(int _x, int _y)
{
	scoreX_ = _x;
	scoreY_ = _y;
}

void CharacterDisplay::SetTimerPosition(int _x, int _y)
{
	timerX_ = _x;
	timerY_ = _y;
}

int CharacterDisplay::GetScore()
{
	return score_;
}
