#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class TitleScene :public GameObject
{
private:
	Transform trPict_;
	short hImage_;
	float wave;


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

