#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class Score :public GameObject
{
private:
	Text* pText_;

	int curScore_ = 0;    // 1�t���[���O�̃X�R�A
	int score_ = 0;       // ���݂̃X�R�A
	int up_ = 0;          // �\���p�X�R�A
	int kill_ = 0;        // �v���C���[���|�����G�̐�
	int jewel_ = 0;       // �v���C���[���W�߂���΂̐�
	int bulletScore_ = 0; // ����̃X�R�A
	int incrementSteps_ = 25; // �X�R�A�𕪊����ĉ��Z�����
	int incrementValue_ = 0; // �X�R�A�̑�����

	int saveScore_ = 0;
	int posX_, posY_;

	bool countUp_ = false;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Score(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	
	int GetScore() {return saveScore_;}
	void SetScore(int score) { score_ = score; }
	void SetDisplayPosition(int x, int y) { posX_ = x; posY_ = y; }

	void ScoreCaluc();
	void Start() { countUp_ = true; }
	void Stop() { countUp_ = false; }
	void SetIncrementSteps(int step) { incrementSteps_ = step; }
};