#include "EnemySpawnPoint.h"
#include "Engine/Debug.h"
#include "Enemy/Enemy.h"

#include "Engine/BoxCollider.h"


//コンストラクタ
EnemySpawnPoint::EnemySpawnPoint(GameObject* parent)
	: GameObject(parent, "EnemySpawnPoint")
{
}

//初期化
void EnemySpawnPoint::Initialize()
{
	BoxCollider* collider = new BoxCollider({ 0,0.5,0 }, { 1.0,1.0,1.0 });
	AddCollider(collider);

}

//更新
void EnemySpawnPoint::Update()
{
}

//描画
void EnemySpawnPoint::Draw()
{
}

//開放
void EnemySpawnPoint::Release()
{
}

void EnemySpawnPoint::SetSpawnPoint(float vertical,float beside)
{
	point.up = vertical;
	point.down = beside;
}
