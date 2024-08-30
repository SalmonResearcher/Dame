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
	int showScoreTime = 0;

	int soundtimer;

	bool countStart[4];

	bool countEnd = false;
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

