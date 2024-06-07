#include "CharacterDisplay.h"

#include "Score.h"
#include "Timer.h"
#include "JewelNumber.h"

#include "Engine/Debug.h"

//�R���X�g���N�^
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),
	pText_(nullptr),scoreX(950),scoreY(25),timerX(800),timerY(25),jewelX(45),jewelY(600), displayScore(true),
	displayTimer(true),displayJewel(true)
{
}

//������
void CharacterDisplay::Initialize()
{

	pScore_ = Instantiate<Score>(this);
	pTimer_ = Instantiate<Timer>(this);
	pJewel_ = Instantiate<JewelNumber>(this);

	pTimer_->SetLimit(30);
}

//�X�V
void CharacterDisplay::Update()
{
}

//�`��
void CharacterDisplay::Draw()
{
	if (displayScore) {
		pScore_->Draw(scoreX, scoreY);
	}
	if (displayTimer) {
		pTimer_->Draw(timerX, timerY);
	}
	if (displayJewel) {
		pJewel_->Draw(jewelX, jewelY);
	}

}

void CharacterDisplay::Draw(int _score)
{
	pScore_->Draw(scoreX, scoreY, _score);
}




//�J��
void CharacterDisplay::Release()
{
}

void CharacterDisplay::ScorePosition(int x, int y)
{
	scoreX = x;
	scoreY = y;
}

void CharacterDisplay::TimerPosition(int x, int y )
{
	timerX = x;
	timerY = y;
}

int CharacterDisplay::GetScore()
{
	return score_;
}
