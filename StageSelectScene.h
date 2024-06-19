#pragma once
#include "Engine/GameObject.h"




class StageSelectScene :
    public GameObject
{
private:




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

