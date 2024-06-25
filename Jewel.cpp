#include "Jewel.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"

//Debug用
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>

namespace {
    float grabity_ = 0.02f;
}


//コンストラクタ
Jewel::Jewel(GameObject* parent)
    :GameObject(parent, "Jewel"), hModel_(-1)
{

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.8f);
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

    hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

    RayCastData data;
    data.start = { transform_.position_ };   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStage_, &data); //レイを発射

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }

}

//更新
void Jewel::Update()
{



    // メインのプログラム
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

//描画
void Jewel::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Jewel::Release()
{
}

void Jewel::Shoot() 
{

}
