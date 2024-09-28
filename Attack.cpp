#include "Attack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy.h"

namespace {
    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;



}

//�R���X�g���N�^
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1), deleteTime_(0), move_{0,0,0}
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), ATTACK_SIZE);
    AddCollider(collision);
}

//�f�X�g���N�^
Attack::~Attack()
{

}

//������
void Attack::Initialize()
{

}

//�X�V
void Attack::Update()
{
    Attacking();
    if (deleteTime_ <= 0)
    {
        KillMe();
    }
    deleteTime_--;

}

//�`��
void Attack::Draw()
{
}

//�J��
void Attack::Release()
{
}

void Attack::OnCollision(GameObject* pTarget)
{
}

void Attack::AttackDirection(XMVECTOR _dir)
{
    playerForwardVec_ = _dir;
}

void Attack::AttackPosition(XMFLOAT3 _pos)
{
    //���̐���ύX����ƍU���̏o���ʒu�������Ȃ�
    float offset = 0.25f;
    playerPos_ = _pos;
    // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
    XMVECTOR attackInit = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * offset);
    XMStoreFloat3(&attackPos_, attackInit);
}

void Attack::Attacking() {
    XMFLOAT3 moveAtk;
    XMStoreFloat3(&moveAtk, playerForwardVec_);
    attackPos_.x += moveAtk.x * ATTACK_SIZE;
    attackPos_.z += moveAtk.z *ATTACK_SIZE;
    transform_.position_ = attackPos_;
}
