#pragma once
#include "Engine/GameObject.h"

//�e�X�g�V�[�����Ǘ�����N���X
class FadeIn_FadeOut : public GameObject
{
private:
	short timer;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	FadeIn_FadeOut(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�t�F�[�h�C����ݒ�
	//�����Fint�@�����܂ł̃t���[���i�f�t�H���g��30F�j
	void FadeIn_B(int _frame);
	//�t�F�[�h�C����ݒ�
	//�����Fint �����܂ł̃t���[���i�f�t�H���g��30F�j
	void FadeIn_B();

	void FadeIn_W();
	void FadeIn_W(int _frame);


	void FadeOut_B();
	void FadeOut_W();

};