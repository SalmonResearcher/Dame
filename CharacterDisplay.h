#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Score;
class Timer;

class CharacterDisplay :public GameObject
{
private:
	Text* pText_;
	Score* pScore_;
	Timer* pTimer_;

	int scoreX, scoreY;
	int timerX, timerY;
	bool displayScore, displayTimer;

	int score_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CharacterDisplay(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	void Draw(int _score);

	//開放
	void Release() override;

	void ScorePosition(int x, int y,bool display);
	void TimerPosition(int x, int y,bool display);

	int GetScore();

};