#pragma once
#include "Engine/GameObject.h"

class TutorialStage;
class Player;

//�e�X�g�V�[�����Ǘ�����N���X
class Tutorial : public GameObject
{
	int hBGM_;

	int hScoreSound_;
	int soundtimer;

	Player* pPlayer_;
	TutorialStage* pStage_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Tutorial(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�T�E���h���ZF���ƂɍĐ�����
	void SoundPlay(int handle, int interval);

};