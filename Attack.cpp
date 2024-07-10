#include "Attack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"
#include "Enemy/Enemy.h"

namespace {
    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;
}

//コンストラクタ
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1), time_(0)
{
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
    AddCollider(collision);
}

//デストラクタ
Attack::~Attack()
{

}

//初期化
void Attack::Initialize()
{

}

//更新
void Attack::Update()
{
    transform_.position_.x = move_.x;
    transform_.position_.y = move_.y;
    transform_.position_.z = move_.z;

    if (time_ <= 0)
    {
        KillMe();
    }
    time_--;

}

//描画
void Attack::Draw()
{
}

//開放
void Attack::Release()
{
}

void Attack::OnCollision(GameObject* pTarget)
{
}

void Attack::AttackDirection(XMVECTOR _dir)
{
    playerForwardVec_ = _dir;
}

void Attack::AttackPosition(XMFLOAT3 _pos)
{
    playerPos_ = _pos;
    // 弾丸の初期位置 = プレイヤー位置 + (前方ベクトル * 距離オフセット)
    XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
    XMStoreFloat3(&bulletPos_, bulletInitPos);
}
