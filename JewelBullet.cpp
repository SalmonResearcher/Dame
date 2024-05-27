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


    //BulletMovementVector(idk what happen,I cant write japanese)
    XMVECTOR frontMove = XMVectorSet(0, 0, 1, 0);		//z���W�ɓ������x

    jewelDir_ += frontMove;

    XMStoreFloat3(&trJBullet_.position_, jewelDir_);

    if (data.hit)
    {
        trJBullet_.position_.y = -data.dist;
    }

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
