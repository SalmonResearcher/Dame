#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"

//Debug用
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>


//コンストラクタ
JewelBullet::JewelBullet(GameObject* parent)
    :GameObject(parent, "JewelBullet"), hModel_(-1), deleteTime_(0)
{

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(collision);
}

//デストラクタ
JewelBullet::~JewelBullet()
{
}

//初期化
void JewelBullet::Initialize()
{
    //Jewel.fbxのモデル座標がずれていて使い物にならない
    hModel_ = Model::Load("JewelBullet.fbx");
    assert(hModel_ >= 0);

    hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

}

//更新
void JewelBullet::Update()
{
    tJBullet_.rotate_.z += 8;
    RayCastData data;
    data.start = { tJBullet_.position_.x,0,tJBullet_.position_.z };   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStage_, &data); //レイを発射

    RayCastData front;
    front.start = { tJBullet_.position_ };   //レイの発射位置
    front.dir = XMFLOAT3(0, 0, 1);       //レイの方向
    Model::RayCast(hStage_, &front); //レイを発射


   
    Shoot();

    tJBullet_.position_.y = -data.dist + 0.5f;
    if (front.dist <1.0f) {
        KillMe();
    }
    transform_ = tJBullet_;
}

//描画
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, tJBullet_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}

void JewelBullet::Shoot()
{
    XMFLOAT3 moveFloat;
    XMStoreFloat3(&moveFloat, playerForwardVec_);

    initPos.x += moveFloat.x * 0.8;
    initPos.z += moveFloat.z * 0.8;

    tJBullet_.position_ = initPos;

}

void JewelBullet::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "JewelBox")
    {
        KillMe();
    }
}

