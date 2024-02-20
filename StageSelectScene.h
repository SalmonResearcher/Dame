#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class StageSelectScene :
    public GameObject
{
private:
	const int MAX_STAGE = 3;

	//���Ȃ�MAX_STAGE���g���Ȃ���
	int hStage_[3];
	//�X�e�[�W�v���r���[�̃g�����X�t�H�[��
	Transform trStage1, trStage2, trStage3;

	int hSkysphere;
	Transform trSky;

	std::string name = "MiniStage";
	std::string num;
	std::string ext = ".fbx";

	//��]�p�̎���
	float timer;

	//�L�[�������ō����X�e�[�W�I��p�^�C�}�[
	float keyTimer;

	//�������㉺��������
	float sinwave;

	//�c�h�ꎞ��
	float yMoveTime;

	//�����Ԗ�
	int stageNum;

	//enum STAGE {

	//};

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StageSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

