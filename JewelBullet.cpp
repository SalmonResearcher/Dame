#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"

//Debug�p
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>


//�R���X�g���N�^
JewelBullet::JewelBullet(GameObject* parent)
    :GameObject(parent, "JewelBullet"), hModel_(-1), time_(0)
{

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(collision);
}

//�f�X�g���N�^
JewelBullet::~JewelBullet()
{
}

//������
void JewelBullet::Initialize()
{
    //Jewel.fbx�̃��f�����W������Ă��Ďg�����ɂȂ�Ȃ�
    hModel_ = Model::Load("JewelBullet.fbx");
    assert(hModel_ >= 0);

    hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();
    tJBullet_.rotate_.y += 180;

}

//�X�V
void JewelBullet::Update()
{
    tJBullet_.rotate_.z += 8;
    RayCastData data;
    data.start = { tJBullet_.position_.x,0,tJBullet_.position_.z };   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStage_, &data); //���C�𔭎�


    // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
    XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 2.0f);
    XMStoreFloat3(&tJBullet_.position_, bulletInitPos);

    // �e�ۂ̈ړ��x�N�g��
    XMVECTOR bulletMoveVec = playerForwardVec_;

    // �e�ۂ̈ʒu���X�V
    XMVECTOR nextBulletPos = XMLoadFloat3(&tJBullet_.position_) + bulletMoveVec;
    XMStoreFloat3(&tJBullet_.position_, nextBulletPos);

    // �`�揈���Ȃ�
    tJBullet_.position_.y = -data.dist + 0.5f;
    transform_ = tJBullet_;
}

//�`��
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, tJBullet_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}


void JewelBullet::Shoot()
{

}
