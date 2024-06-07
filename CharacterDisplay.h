#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Score;
class Timer;
class JewelNumber;

class CharacterDisplay :public GameObject
{
private:
	Text* pText_;
	Score* pScore_;
	Timer* pTimer_;
	JewelNumber* pJewel_;


	int scoreX, scoreY;
	int timerX, timerY;
	int jewelX, jewelY;

	bool displayScore, displayTimer,displayJewel;

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

	void ScorePosition(int x, int y);
	void TimerPosition(int x, int y);

	void HideScore() { displayScore = false; };
	void HideTimer() { displayTimer = false; };
	void HideJewel() { displayJewel = false; };

	int GetScore();

};