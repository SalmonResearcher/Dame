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
	bool spawn = true;
	int timer = 0;
	int count = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;
	JewelBox* pBox;
	CharacterDisplay* pDisplay;

	Text* pText;

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