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

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CharacterDisplay(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	void Draw(int _score);

	//�J��
	void Release() override;

	void ScorePosition(int x, int y);
	void TimerPosition(int x, int y);

	void HideScore() { displayScore = false; };
	void HideTimer() { displayTimer = false; };
	void HideJewel() { displayJewel = false; };

	int GetScore();

};