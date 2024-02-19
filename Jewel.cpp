#include "Jewel.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Engine/Debug.h"

#include <cmath>


//�R���X�g���N�^
Jewel::Jewel(GameObject* parent)
    :GameObject(parent, "Jewel"), hModel_(-1), time(0),jewelRotate_(false)
{

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.8f);
    AddCollider(collision);
}

//�f�X�g���N�^
Jewel::~Jewel()
{
}

//������
void Jewel::Initialize()
{
    hModel_ = Model::Load("Jewel.fbx");
    assert(hModel_ >= 0);

}

//�X�V
void Jewel::Update()
{
    hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

    RayCastData data;
    data.start = { trJewel_.position_ };   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStage_, &data); //���C�𔭎�

    if (data.hit)
    {
        //if (data.dist <= 0.1f)
        //{
        //    grabity_ = 0.0f;
        //}
        //else
        //{
        //    grabity_ = 0.3f;
        //}

        //trJewel_.position_.y -= grabity_;
        trJewel_.position_.y = -data.dist;

    }


    //trJewel_.position_.y = (float)sin(time)/50;

    // ���C���̃v���O����
    if (time % 75 == 0) {
        jewelRotate_ = true;
    }

    if (jewelRotate_) {
        float easingFactor = easeInOutCubic(static_cast<float>(rotY) / 360.0f);
        trJewel_.rotate_.y = rotY * easingFactor;

        rotY += 5.5f;
        if (rotY >= 360) {
            rotY = 0;
            jewelRotate_ = false;
        }
    }

    Debug::Log("rotate = ");
    Debug::Log(rotY);

    time++;
    transform_ = trJewel_;
}

//�`��
void Jewel::Draw()
{
    Model::SetTransform(hModel_, trJewel_);
    Model::Draw(hModel_);
}

void Jewel::Release()
{
}
