#include "Jewel.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "TutorialStage.h"
#include "Player.h"



#include <cmath>

namespace {
    float grabity_ = 0.02f;
}


//�R���X�g���N�^
Jewel::Jewel(GameObject* parent)
    :GameObject(parent, "Jewel"), hModel_(-1),stopEmit_(false)
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
    if (time_ % 70 == 0 && !stopEmit_) {
        CreateVFX();
    }


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

void Jewel::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")
    {
        VFX::End(hEmit_);
        KillMe();
    }
}

void Jewel::CreateVFX()
{
    vfx.textureFileName = "paticleAssets/FlashB_B.png";
    vfx.position = (transform_.position_);
    vfx.number = 1;
    vfx.positionRnd = XMFLOAT3(0.8, 0, 0.8);
    vfx.direction = XMFLOAT3(0, 1, 0);
    vfx.directionRnd = XMFLOAT3(10, 10, 10);
    vfx.size = XMFLOAT2(1.5, 1.5);
    vfx.scale = XMFLOAT2(0.99, 0.99);
    vfx.lifeTime = 35;
    vfx.speed = 0.05f;
    vfx.spin = XMFLOAT3(0, 0, 0.1f);
    vfx.gravity = 0;
    vfx.delay = 0;
    hEmit_ = VFX::Start(vfx);

}

void Jewel::DestroyVFX()
{
    stopEmit_ = true;
}

