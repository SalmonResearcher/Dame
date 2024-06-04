#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"
#include "JewelBox.h"

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

    if (deleteTime_ >= 180)
    {
        KillMe();
    }

    transform_ = tJBullet_;
    deleteTime_++;
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
    if (pTarget->GetObjectName() == "Enemy")
    {
        pTarget->GetParent();
        killCount_++;
    }

    if (pTarget->GetObjectName() == "JewelBox")
    {
        score_ = CalculateScore(killCount_);
        ((JewelBox*)FindObject("JewelBox"))->AddScore(score_);
        KillMe();
    }
}

int JewelBullet::CalculateScore(int killCount)
{
    int baseScore = 200; // 固定の200点
    std::vector<int> scores = { 25, 50, 75, 150, 300, 3000 };

    //倒した数が1～4の時
    if (killCount >= 1 && killCount < 5) {
        return scores[killCount - 1] + baseScore;
    }
    //敵を倒した数が5以上の時
    else if (killCount >= 5 && killCount < 10) {
        return scores[4] * (killCount - 4) + baseScore; // 6の時は300*2、7の時は300*3となる
    }
    else if (killCount >= 10) {
        return scores[5] * (killCount - 9) + baseScore;
    }
    else {
        return baseScore; // killCountが0以下の時は宝石のみの点
    }
}