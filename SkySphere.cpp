#include "SkySphere.h"
#include "Player.h"

#include "Engine/Model.h"

//コンストラクタ
SkySphere::SkySphere(GameObject* parent)
    :GameObject(parent, "SkySphere"), hModel_(-1)
{
}

//デストラクタ
SkySphere::~SkySphere()
{
}

//初期化
void SkySphere::Initialize()
{
    hModel_ = Model::Load("SkySphere.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = SCALE;
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

//更新
void SkySphere::Update()
{
    transform_.rotate_.y += ROTATE_SPEED;
    transform_.position_ = pPlayer_->GetPlayerPosition();
}

//描画
void SkySphere::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void SkySphere::Release()
{
}