#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class TitleScene :public GameObject
{
private:

	int hBGM_;

	enum
	{
		BG,
		SLIME,
		GROUND,
		HUMAN,
		LOGO,
		MAX_IMAGE
	};

	int hImage_[MAX_IMAGE];
	Transform trImage_[MAX_IMAGE];

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

