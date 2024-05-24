#include "EnemySpawnPoint.h"
#include "Engine/Debug.h"
#include "Enemy/Enemy.h"

#include "Engine/BoxCollider.h"


//�R���X�g���N�^
EnemySpawnPoint::EnemySpawnPoint(GameObject* parent)
	: GameObject(parent, "EnemySpawnPoint")
{
}

//������
void EnemySpawnPoint::Initialize()
{
	BoxCollider* collider = new BoxCollider({ 0,0.5,0 }, { 1.0,1.0,1.0 });
	AddCollider(collider);

}

//�X�V
void EnemySpawnPoint::Update()
{
}

//�`��
void EnemySpawnPoint::Draw()
{
}

//�J��
void EnemySpawnPoint::Release()
{
}

void EnemySpawnPoint::SetSpawnPoint(float vertical,float beside)
{
	point.up = vertical;
	point.down = beside;
}
