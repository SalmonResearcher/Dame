#include "EnemySpawn.h"

#include "Enemy/Enemy.h"

//�R���X�g���N�^
EnemySpawn::EnemySpawn(GameObject* parent)
    :GameObject(parent, "EnemySpawn"), interval_(25),time_(0)
{
}

//�f�X�g���N�^
EnemySpawn::~EnemySpawn()
{
}

//������
void EnemySpawn::Initialize()
{
    srand(static_cast<unsigned int>(time(0)));
}

//�X�V
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

//�`��
void EnemySpawn::Draw()
{
}

//�J��
void EnemySpawn::Release()
{
}

float EnemySpawn::getRandomFloat(float min, float max)
{
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + random * (max - min);
}

