#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	int hImage_;

	CharacterDisplay* pDisp1_;
	CharacterDisplay* pDisp2_;
	CharacterDisplay* pDisp3_;
	CharacterDisplay* pDisp4_;

	int killCount_;
	int jewel_;
	int jewelKill_;

	int totalScore_;

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

};

