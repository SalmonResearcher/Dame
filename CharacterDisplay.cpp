#include "CharacterDisplay.h"
#include "Score.h"
#include "Timer.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//コンストラクタ
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),
	pText_(nullptr),scoreX(950),scoreY(450),timerX(800),timerY(5),displayScore(true),
	displayTimer(true)
{
}

//初期化
void CharacterDisplay::Initialize()
{

	pScore_ = Instantiate<Score>(this);
	pTimer_ = Instantiate<Timer>(this);

	pTimer_->SetLimit(30);
	pTimer_->Start();

}

//更新
void CharacterDisplay::Update()
{
}

//描画
void CharacterDisplay::Draw()
{
	if (displayScore) {
		pScore_->Draw(scoreX, scoreY);
	}
	if (displayTimer) {
		pTimer_->Draw(timerX, timerY);
	}

}

void CharacterDisplay::Draw(int _score)
{
	pScore_->Draw(scoreX, scoreY, _score);
}




//開放
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
