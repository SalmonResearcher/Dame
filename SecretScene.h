#pragma once
#include "Engine/GameObject.h"
class SecretScene :public GameObject
{
private:
	int hModel_;
	int countDown;

	public:

		//�R���X�g���N�^
		//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
		SecretScene(GameObject* parent);

		//������
		void Initialize() override;

		//�X�V
		void Update() override;

		//�`��
		void Draw() override;

		//�J��
		void Release() override;

};



