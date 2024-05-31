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
    :GameObject(parent, "JewelBullet"), hModel_(-1), time_(0)
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
   
    XMFLOAT3 moveFloat;
    XMStoreFloat3(&moveFloat ,playerForwardVec_);

    initPos.x += moveFloat.x * 0.2;
    initPos.z += moveFloat.z * 0.2;

    tJBullet_.position_ = initPos;

    tJBullet_.position_.y = -data.dist + 0.5f;
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

