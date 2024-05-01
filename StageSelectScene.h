#pragma once
#include "Engine/GameObject.h"

#include "Engine/Text.h"

#include <string.h>

class StageSelectScene :
    public GameObject
{
private:
	Text* pText;

	enum
	{
		STAGE1,
		STAGE2,
		STAGE3,
		MAX_STAGE
	};

	int hStage_[MAX_STAGE];
	Transform trStage[MAX_STAGE];	//�X�e�[�W�v���r���[�̃g�����X�t�H�[��
	
	int hImage_[2];
	Transform trImage_[2];

	XMFLOAT3 cameraPos;
	float moveX;

	int hSkysphere;
	Transform trSky;

	std::string name = "MiniStage";
	std::string num;
	std::string ext = ".fbx";

	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };

	//��]�p�̎���
	float timer;

	//�c�h�ꎞ��
	float yMoveTime;

	//�������㉺��������
	float sinwave;

	//�X�e�[�W�I������Ƃ��̃J�E���g
	int selectCount = 0;

	bool flg = false;

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

	void StageScaling(Transform* stage_, bool big , float rate);

};

