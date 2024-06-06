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

	int scoreX_, scoreY_;
	int timerX_, timerY_;
	bool showScore_, showTimer_;

	int score_;
	int timer_;

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
	void DrawScore();
	void DrawScore(int _score);
	void DrawTimer();

	//�J��
	void Release() override;

	void SetScorePosition(int _x, int _y);
	void SetTimerPosition(int _x, int _y);

	int GetScore();

	void ShowScore() { showScore_ = true; };
	void HideScore() { showScore_ = false; };

	void ShowTimer() { showTimer_ = true; };
	void HideTimer() { showTimer_ = false; };
};