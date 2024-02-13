#include "Attack.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "Player.h"

//コンストラクタ
Attack::Attack(GameObject* parent)
    :GameObject(parent, "Attack"), hModel_(-1),time(0)
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

    if (time >= 9)
    {
        KillMe();
    }
    time++;

}

//描画
void Attack::Draw()
{
}

//開放
void Attack::Release()
{
}