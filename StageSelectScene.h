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

	enum
	{
		IMAGE_1,
		IMAGE_2,
		MAX_IMAGE
	};
	XMFLOAT3 cameraPos;


	int hSkysphere;
	Transform trSky;

	int hBGM_;
	int hImage_[MAX_IMAGE];
	int hStage_[MAX_STAGE];

	int alImage_[MAX_IMAGE];	//alpha�l

	Transform trStage[MAX_STAGE];	//�X�e�[�W�v���r���[�̃g�����X�t�H�[��
	Transform trImage_[MAX_IMAGE];

	//�~�j�X�e�[�W�̈ړ�
	float moveX;
	//���E�́����̓���
	float moveXImage;

	//�X�e�[�W�̈ړ���
	const float STAGE_MOVE = 0.25f;

	//��]�p�̎���
	float timer_;

	//�c�ɗh��鑬��
	const float Y_MOVE_SPEED = 0.06f;

	//�X�e�[�W�I������Ƃ��̃J�E���g
	int selectCount_;

	//���̃X�e�[�W�Ŏ~�܂������ǂ���
	bool isStageStop = false;

	//�c�h�ꎞ��
	float yMoveTime;

	//�������㉺������ϐ�
	float sinwave;

	const float STAGE_ROTATE_SPEED = 3.0f;
	const float WAVE_VELOCITY = 5.0f;
	const float SCALE_UP_SPEED = 0.03f;
	const float SCALE_DOWN_SPEED = 0.05f;
	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };

	//�ő�
	const XMFLOAT3 IMAGE_SCALE = { 0.3,0.3,0.3 };
	const int IMAGE_MAX_ALPHA = 192;		//�摜�̍ő�s�����x
	const int IMAGE_ROTATE = 180;			//�摜�̉�]
	const float IMAGE_POSITiON = 0.8f;		//�摜�̈ʒu
	const int IMAGE_WAVE_VEL = 100;			//�摜�̉��h��̂悳

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

