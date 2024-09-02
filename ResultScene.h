#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	int hImage_;
	int hCountSound_;
	int hMoneySound_;

	int hBGM_;

	float pitch_;

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


	//�X�R�A�\�����̒萔����
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

