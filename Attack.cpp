#include "Attack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"

//�R���X�g���N�^
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1),time(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
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
    transform_.position_.x = move_.x;
    transform_.position_.y = move_.y;
    transform_.position_.z = move_.z;

    if (time >= 9)
    {
        KillMe();
    }
    time++;

}

//�`��
void Attack::Draw()
{
}

//�J��
void Attack::Release()
{
}