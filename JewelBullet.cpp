#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"
#include "Enemy/Enemy.h"
#include "JewelBox.h"

//Debug用
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>
#include "Global.h"

namespace {

    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;
}

//コンストラクタ
JewelBullet::JewelBullet(GameObject* parent)
    :GameObject(parent, "JewelBullet"), hModel_(-1)
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
    transform_.rotate_.z += 8;

    //壁にぶつかったら消える
    RayCastData front;
    front.start = { transform_.position_ };   //レイの発射位置
    front.dir = XMFLOAT3(0, 0, 1);       //レイの方向
    Model::RayCast(hStage_, &front); //レイを発射
   
    Shoot();


    if (front.dist <1.5f) {
        KillMe();
    }

    if (deleteTime_ >= 180)
    {
        KillMe();
        killCount_ = 0;
    }
    deleteTime_++;

    Debug::Log("宝石で敵を倒した数 = ");
    Debug::Log(killCount_, true);
    
}

//描画
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}

void JewelBullet::BulletDirection(XMVECTOR _dir)
{
    playerForwardVec_ = _dir;
}

void JewelBullet::BulletPosition(XMFLOAT3 _pos)
{
    playerPos_ = _pos;
    // 弾丸の初期位置 = プレイヤー位置 + (前方ベクトル * 距離オフセット)
    XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
    XMStoreFloat3(&bulletPos_, bulletInitPos);
};

void JewelBullet::Shoot()
{
    XMFLOAT3 moveFloat;
    XMStoreFloat3(&moveFloat, playerForwardVec_);

    bulletPos_.x += moveFloat.x * 0.8;
    bulletPos_.z += moveFloat.z * 0.8;

    transform_.position_ = bulletPos_;

}

void JewelBullet::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Enemy")
    {
        Enemy* pEnemy = (Enemy*)pTarget;
        pEnemy->Death();
    }

    if (pTarget->GetObjectName() == "JewelBox")
    {
        score_ = CalculateScore(killCount_);
        ((JewelBox*)FindObject("JewelBox"))->AddScore(score_);
        if (score_ != 200)
        {
            Global::AddJewelKill(score_);
        }
        Global::AddJewel(1);
        killCount_ = 0;
        KillMe();
    }
}

int JewelBullet::CalculateScore(int killCount)
{
    int baseScore = 200; // 固定の200点
    int scores[] = {25, 50, 75, 150, 300, 1500};

    //倒した数が1～4の時
    if (killCount >= 1 && killCount < 5) {
        return scores[killCount - 1] + baseScore;
    }
    //敵を倒した数が5以上の時
    else if (killCount >= 5 && killCount < 10) {
        return scores[4] * (killCount - 4) + baseScore; // 6の時は300*2、7の時は300*3となる
    }
    //10以上1500*kill-8
    else if (killCount >= 10) {
        return scores[5] * (killCount - 8) + baseScore;
    }
    else {
        return baseScore; // killCountが0以下の時は宝石のみの点
    }
}

void JewelBullet::SetKillCount(int count)
{
    killCount_ += count;
}
