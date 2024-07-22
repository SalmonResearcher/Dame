#include "Jewel.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "TutorialStage.h"
#include "Player.h"

//Debug�p
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>

namespace {
    float grabity_ = 0.02f;
}


//�R���X�g���N�^
Jewel::Jewel(GameObject* parent)
    :GameObject(parent, "Jewel"), hModel_(-1)
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

    hStage_ = SetStageHandle();

    RayCastData data;
    data.start = { transform_.position_ };   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStage_, &data); //���C�𔭎�

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }

}

//�X�V
void Jewel::Update()
{



    // ���C���̃v���O����
    if (time_ % 90 == 0) {
        jewelRotate_ = true;
    }

    if (jewelRotate_) {
        float easingFactor = easeInOutCubic(static_cast<float>(rotY) / 360.0f);
        transform_.rotate_.y = rotY * easingFactor;

        rotY += 5.5f;
        if (rotY >= 360) {
            rotY = 0;
            jewelRotate_ = false;
        }
    }

    time_++;
    transform_ = transform_;
}

//�`��
void Jewel::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Jewel::Release()
{
}

int Jewel::SetStageHandle()
{
    if ((FindObject("Stage")) != nullptr)
    {
        return ((Stage*)FindObject("Stage"))->GetModelHandle();
    }
    else if ((FindObject("TutorialStage")) != nullptr)
    {
        return ((TutorialStage*)FindObject("TutorialStage"))->GetModelHandle();
    }
    return -1;
}