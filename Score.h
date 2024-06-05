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
	void Draw(int _x, int _y);

	//�J��
	void Release() override;

};