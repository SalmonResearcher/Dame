#include "JewelBox.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Player.h"

//コンストラクタ
JewelBox::JewelBox(GameObject* parent)
    :GameObject(parent, "JewelBox"), hModel_(-1), anim_Start(0), anim_End(13),anim_Speed(1)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 3.2f);
    AddCollider(collision);
}

//デストラクタ
JewelBox::~JewelBox()
{
}

//初期化
void JewelBox::Initialize()
{
    hModel_ = Model::Load("Box.fbx");
    assert(hModel_ >= 0);

    trBox_.position_.y = -97;
}

//更新
void JewelBox::Update()
{
    transform_ = trBox_;
}

//描画
void JewelBox::Draw()
{
    Model::SetTransform(hModel_, trBox_);
    Model::Draw(hModel_);

    Model::SetAnimFrame(hModel_, anim_Start, anim_End, anim_Speed);
}

//開放
void JewelBox::Release()
{
}

void JewelBox::OnCollision(GameObject* pTarget)
{
        if (pTarget->GetObjectName() == "Attack")
        {
            anim_Start = 0;
            anim_End = 12;
        }
}
