#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Player;
class Stage;
class Jewel;
class Enemy;
class JewelBox;
class CharacterDisplay;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	bool spawn_ = true;
	int timer_ = 0;
	int count_ = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	Player* pPlayer_;
	Stage* pStage_;
	Jewel* pJewel_;
	Enemy* pEnemy_;
	JewelBox* pBox_;
	CharacterDisplay* pDisplay_;

	Text* pText_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};