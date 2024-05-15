#include "EnemyAttack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy/Enemy.h"

//�R���X�g���N�^
EnemyAttack::EnemyAttack(GameObject* parent)
    :GameObject(parent, "EnemyAttack"), hModel_(-1), time(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
    AddCollider(collision);
}

//�f�X�g���N�^
EnemyAttack::~EnemyAttack()
{
}

//������
void EnemyAttack::Initialize()
{

}

//�X�V
void EnemyAttack::Update()
{
    
    transform_.position_.x = move_.x;
    transform_.position_.y = move_.y;
    transform_.position_.z = move_.z;

    if (time == 0)
    {
        KillMe();
    }
    time--;

}

//�`��
void EnemyAttack::Draw()
{
}

//�J��
void EnemyAttack::Release()
{
}

void EnemyAttack::OnCollision(GameObject* pTarget)
{
}
