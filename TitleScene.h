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
		PRESS,
		MAX_IMAGE
	};

	int hImage_[MAX_IMAGE];
	Transform trImage_[MAX_IMAGE];

	//�h����
	float frequency_;

	//�傫�����ő�ɂȂ�܂ł̑��x
	const float SCALE_SPEED = 0.05f;

	//�ő�̑傫��
	const float MAX_SCALE = 0.05f;

	//�U�ꕝ���ő�ɂȂ�܂ł̑��x
	const float SWAY_SPEED = 0.5f;
	const float HUMAN_SWAY_SPEED = 2.0f;

	//�U�ꕝ�̑傫��
	const float SWAY_AMPLITUDE = 0.05f;

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

