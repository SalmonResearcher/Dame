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
	pText_(nullptr),scoreX(950),scoreY(5),timerX(800),timerY(5),displayScore(true),
	displayTimer(true)
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
	if (displayScore) {
		pScore_->Draw(scoreX, scoreY);
		score_ = pScore_->GetScore();
	}
	if (displayTimer) {
		pTimer_->Draw(timerX, timerY);
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

void CharacterDisplay::ScorePosition(int x, int y,bool display)
{
	scoreX = x;
	scoreY = y;
	displayScore = display;
}

void CharacterDisplay::TimerPosition(int x, int y ,bool display)
{
	timerX = x;
	timerY = y;
	displayTimer = display;
}

int CharacterDisplay::GetScore()
{
	return score_;
}
