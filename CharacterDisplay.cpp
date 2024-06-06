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
	pText_(nullptr),scoreX_(950),scoreY_(5),timerX_(800),timerY_(5),showScore_(false),showTimer_(false)
{
}

//初期化
void CharacterDisplay::Initialize()
{
	pText_ = new Text;
	pText_->Initialize("score_number.png", 50, 256, 10);
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
	if (showScore_) {
		// 6桁で0埋めのフォーマット指定子を使用して文字列を生成
		char buffer[7]; // 文字列+1分の配列サイズ
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



//開放
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
