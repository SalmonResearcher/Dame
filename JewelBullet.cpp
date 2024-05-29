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

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.8f);
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
}

//�X�V
void JewelBullet::Update()
{
    RayCastData data;
    data.start = { trJBullet_.position_.x,0,trJBullet_.position_.z };   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStage_, &data); //���C�𔭎�


    // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
    XMVECTOR bulletInitPos = XMLoadFloat3(&startPos_) + (jewelDir_ * 2.0f);
    XMStoreFloat3(&trJBullet_.position_, bulletInitPos);

    // �e�ۂ̈ړ��x�N�g�� = �v���C���[�̑O���x�N�g��
    XMVECTOR bulletMoveVector = jewelDir_;

    // �e�ۂ̈ʒu���X�V
    jewelDir_ += bulletMoveVector * 0.01f;
    XMStoreFloat3(&trJBullet_.position_, jewelDir_);

    // �`�揈���Ȃ�
    transform_ = trJBullet_;
}

//�`��
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, trJBullet_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}


void JewelBullet::Shoot()
{

}
