#include "Jewel.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "TutorialStage.h"
#include "Player.h"
#include "Global.h"

#include <cmath>

// コンストラクタ
Jewel::Jewel(GameObject* parent)
    : GameObject(parent, "Jewel"), hModel_(-1), stopEmit_(false)
{
    SphereCollider* collision = new SphereCollider(COLLIDER_POSITION, COLLIDER_RADIUS);
    AddCollider(collision);
}

//デストラクタ
Jewel::~Jewel()
{
}

//初期化
void Jewel::Initialize()
{

    hModel_ = Model::Load("Jewel.fbx");
    assert(hModel_ >= 0);

    hStage_ = SetStageHandle();

    RayCastData data;
    data.start = { transform_.position_ };   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStage_, &data); //レイを発射

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }
    Global::SetJewelScore(JEWEL_BASE_SCORE);
}

//更新
void Jewel::Update()
{
    if (time_ % CREATE_VFX_TIME == 0 && !stopEmit_) {
        CreateVFX();
    }


    // メインのプログラム
    if (time_ % ROTATION_JEWEL_TIME == 0) {
        jewelRotate_ = true;
    }

    if (jewelRotate_) {
        float easingFactor = easeInOutCubic(static_cast<float>(rotY) / MAX_ROTATE);
        transform_.rotate_.y = rotY * easingFactor;

        rotY += ROTATION_SPEED;
        if (rotY >= MAX_ROTATE) {
            rotY = 0;
            jewelRotate_ = false;
        }
    }

    time_++;
}

//描画
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
    vfx.positionRnd = PARTICLE_POSITION_RND;
    vfx.direction = PARTICLE_DIRECTION;
    vfx.directionRnd = PARTICLE_DIRECTION_RND;
    vfx.size = PARTICLE_SIZE;
    vfx.scale = PARTICLE_SCALE;
    vfx.lifeTime = PARTICLE_LIFETIME;
    vfx.speed = PARTICLE_SPEED;
    vfx.spin = PARTICLE_SPIN;
    vfx.gravity = PARTICLE_GRAVITY;
    vfx.delay = PARTICLE_DELAY;
    hEmit_ = VFX::Start(vfx);

}

void Jewel::DestroyVFX()
{
    stopEmit_ = true;
}

