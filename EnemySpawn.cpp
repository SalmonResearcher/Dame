#include "EnemySpawn.h"

#include "Enemy/Enemy.h"

//コンストラクタ
EnemySpawn::EnemySpawn(GameObject* parent)
    :GameObject(parent, "EnemySpawn"), interval_(25),time_(0)
{
}

//デストラクタ
EnemySpawn::~EnemySpawn()
{
}

//初期化
void EnemySpawn::Initialize()
{
    srand(static_cast<unsigned int>(time(0)));
}

//更新
void EnemySpawn::Update()
{

    if (canSpawn_)
    {
        transform_.position_.x = getRandomFloat(minX_,maxX_);
        if ((time_ % interval_) == 0)
        {
            Enemy* pEnemy = Instantiate<Enemy>(GetParent());
            
        }
        time_++;
    }
}

//描画
void EnemySpawn::Draw()
{
}

//開放
void EnemySpawn::Release()
{
}

float EnemySpawn::getRandomFloat(float min, float max)
{
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + random * (max - min);
}

