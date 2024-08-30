#pragma once
#include "Engine/GameObject.h"




class StageSelectScene :
    public GameObject
{
private:

	enum
	{
		STAGE1,
		STAGE2,
		MAX_STAGE
	};


	int hBGM_;
	int hImage_[2];
	int hStage_[MAX_STAGE];

	Transform trStage[MAX_STAGE];	//�X�e�[�W�v���r���[�̃g�����X�t�H�[��
	Transform trImage_[2];


	//�X�e�[�W�I������Ƃ��̃J�E���g
	int selectCount = 0;

	//���̃X�e�[�W�Ŏ~�܂������ǂ���
	bool isStageStop = false;

	XMFLOAT3 cameraPos;

	//�c�h�ꎞ��
	float yMoveTime;

	//�������㉺
	float sinwave;

	const float STAGE_ROTATE_SPEED = 3.0f;
	const float WAVE_VELOCITY = 5.0f;
	const float SCALE_UP_SPEED = 0.03f;
	const float SCALE_DOWN_SPEED = 0.05f;
	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };
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

	//�v���r���[�̃T�C�Y��ύX�Btrue�ő傫���Afase�ŏ������Ȃ�
	void StageScaling(Transform* stage_, bool big);

	//true�Ŋg��A����ȊO�ŏk������֐�
	void StageScaling(Transform* stage_, bool big , float rate);

};

