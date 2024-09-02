#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class JewelNumber :public GameObject
{
private:
	int jewel_= 0;
	Text* pText_;

	int posX_,posY_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	JewelNumber(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetJewelPosition(int x, int y) { posX_ = x; posY_ = y; }
	void SetJewelNumber(int value) { jewel_ = value; }
};