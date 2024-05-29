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

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.8f);
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
    RayCastData data;
    data.start = { trJBullet_.position_.x,0,trJBullet_.position_.z };   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hStage_, &data); //レイを発射


    // 弾丸の初期位置 = プレイヤー位置 + (前方ベクトル * 距離オフセット)
    XMVECTOR bulletInitPos = XMLoadFloat3(&startPos_) + (jewelDir_ * 2.0f);
    XMStoreFloat3(&trJBullet_.position_, bulletInitPos);

    // 弾丸の移動ベクトル = プレイヤーの前方ベクトル
    XMVECTOR bulletMoveVector = jewelDir_;

    // 弾丸の位置を更新
    jewelDir_ += bulletMoveVector * 0.01f;
    XMStoreFloat3(&trJBullet_.position_, jewelDir_);

    // 描画処理など
    transform_ = trJBullet_;
}

//描画
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, trJBullet_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}


void JewelBullet::Shoot()
{

}
