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
	XMFLOAT3 prevS1, prevS2,prevS3;
	int anime;

	int hSkysphere;
	Transform trSky;

	std::string name = "MiniStage";
	std::string num;
	std::string ext = ".fbx";

	const XMFLOAT3 Stage1Scale = { 0.4f,0.4f,0.4f };
	const XMFLOAT3 Stage2Scale = { 0.4f,0.4f,0.4f };
	const XMFLOAT3 Stage3Scale = { 0.4f,0.4f,0.4f };


	//��]�p�̎���
	float timer;

	//�L�[�������ō����X�e�[�W�I��p�^�C�}�[
	int keyTimer;

	//�c�h�ꎞ��
	float yMoveTime;

	//�������㉺��������
	float sinwave;

	//�X�e�[�W�I������Ƃ��̃J�E���g
	int selectCount = 0;

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

	float MoveStages(Transform start, Transform end);
};

