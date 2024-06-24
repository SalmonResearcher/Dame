#include "EnemyAttack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy/Enemy.h"

namespace {
    float colliderScale = 3.5f;
}

//コンストラクタ
EnemyAttack::EnemyAttack(GameObject* parent)
    :GameObject(parent, "EnemyAttack"), hModel_(-1), time_(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), colliderScale);
    AddCollider(collision);
}

//デストラクタ
EnemyAttack::~EnemyAttack()
{
}

//初期化
void EnemyAttack::Initialize()
{

}

//更新
void EnemyAttack::Update()
{

    transform_.position_ = pos_;
    if (time_ == 0)
    {
        KillMe();
    }
    time_--;

}

//描画
void EnemyAttack::Draw()
{
}

//開放
void EnemyAttack::Release()
{
}

void EnemyAttack::OnCollision(GameObject* pTarget)
{
}
