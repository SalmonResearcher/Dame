#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

enum ENEMIES {
	SLIME = 0,
	B_SLIME
};

class EnemySpawnPoint :public GameObject
{
private:
	//std::vector<std::vector<float>> spawner; // �G�̗N���ʒu���Ǘ�����񎟌��z��
	struct Rect {
		float up = 1;
		float down = 1;
	};
	Rect point;


public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EnemySpawnPoint(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetSpawnPoint(float vertical, float beside);
	void SetPosition(XMFLOAT3 _pos)
	{
		transform_.position_ = _pos;
	}

	//�X�|�[���Ԋu�i�����_����+-10F�ł����������j
	void SetSpawnInterval(float interval);

	void SpawnPointChange();

};