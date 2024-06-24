#include "EnemyAttack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy/Enemy.h"

namespace {
    float colliderScale = 3.5f;
}

//�R���X�g���N�^
EnemyAttack::EnemyAttack(GameObject* parent)
    :GameObject(parent, "EnemyAttack"), hModel_(-1), time_(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), colliderScale);
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

    transform_.position_ = pos_;
    if (time_ == 0)
    {
        KillMe();
    }
    time_--;

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
