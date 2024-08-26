#include "JewelBox.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"

#include "Player.h"
#include "Stage.h"
#include "TutorialStage.h"
#include "JewelBullet.h"

//コンストラクタ
JewelBox::JewelBox(GameObject* parent)
    :GameObject(parent, "JewelBox"), hModel_(-1), anim_Start(0), anim_End(10),anim_Speed(1)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1.0f, 0), 1.5f);
    AddCollider(collision);
}

//デストラクタ
JewelBox::~JewelBox()
{
}

//初期化
void JewelBox::Initialize()
{
    int hStage = SetStageHandle();

    hModel_ = Model::Load("Box.fbx");
    assert(hModel_ >= 0);

    RayCastData down;
    down.start = { 0,0,0 };   //レイの発射位置
    down.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStage, &down); //レイを発射


    transform_.position_.y = -down.dist;
}

//更新
void JewelBox::Update()
{
    jewel_ =  ((Player*)FindObject("Player"))->SendJewel();
}

//描画
void JewelBox::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void JewelBox::Release()
{
}

void JewelBox::OnCollision(GameObject* pTarget)
{
}

int JewelBox::SetStageHandle()
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

