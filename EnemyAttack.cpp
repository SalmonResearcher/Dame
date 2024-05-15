#include "EnemyAttack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy/Enemy.h"

//コンストラクタ
EnemyAttack::EnemyAttack(GameObject* parent)
    :GameObject(parent, "EnemyAttack"), hModel_(-1), time(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
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
    
    transform_.position_.x = move_.x;
    transform_.position_.y = move_.y;
    transform_.position_.z = move_.z;

    if (time == 0)
    {
        KillMe();
    }
    time--;

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
