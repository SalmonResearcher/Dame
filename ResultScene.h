#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	enum
	{
		KILL_COUNT,
		JEWEL_COUNT,
		JEWEL_KILL_COUNT,
		TOTAL_SCORE,
		MAX_DISPLAY
	};

	int hImage_;
	Transform trPict_;

	int hCountSound_;
	int hMoneySound_;

	int hBGM_;

	float pitch_;

	const int MAX_SCORE = 999999;

	CharacterDisplay* pDisp_;

	int killCount_;
	int jewel_;
	int jewelKill_;

	int totalScore_;
	int showScoreTime;

	int soundtimer;

	bool countStart[4];

	bool countEnd = false;

	int currentCaseIndex; // ���݂̃P�[�X��ǐՂ���ϐ�

	//�X�R�A�̈ʒu�Ȃ�
	const int SCORE_POSITION_X = 780;
	const int KILL_SCORE_POSITION_Y = 200;
	const int JEWEL_SCORE_POSITION_Y = 335;
	const int JEWEL_KILL_SCORE_POSITION_Y = 470;
	const int TOTAL_SCORE_POSITION_Y = 605;

	const int DEFAULT_INCREMENT_STEP = 30; //�g�[�^���X�R�A�ȊO�̉��Z��
	const int TOTAL_SCORE_INCREMENT_STEP = 120;	//�g�[�^���X�R�A�̉��Z��

	const int DEFAULT_SCORE_INCREMENT_FRAMES = 30; // �f�t�H���g�̃t���[����
	const int TOTAL_SCORE_INCREMENT_FRAMES = 120;  // �g�[�^���X�R�A�̃t���[����

	//�X�R�A�\�����̒萔
	enum ScoreCountTimes
	{
		START_SCORE_COUNT_0 = 30,
		START_SCORE_COUNT_1 = 90,
		START_SCORE_COUNT_2 = 150,
		START_SCORE_COUNT_3 = 240,
		MAX_SHOW_SCORE_TIME = 360,
		SOUND_PLAY_INTERVAL = 5
	};

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SoundPlay(int handle,int interval);

	void SoundStop(int handle);

};

