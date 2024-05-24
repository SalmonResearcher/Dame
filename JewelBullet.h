#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class JewelBullet :public GameObject
{
private:
	Text* pText;

	int kill_;
	int score_ = 0;


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	JewelBullet(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};