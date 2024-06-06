#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	short hImage_;
	CharacterDisplay* pDisplay_;

	int score_;

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

