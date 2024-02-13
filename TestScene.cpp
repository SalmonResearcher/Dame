#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Player* pPlayer = Instantiate<Player>(this);
	Stage* pStage = Instantiate<Stage>(this);


}

//�X�V
void TestScene::Update()
{
	for (int c = 0; c < 50; c++)
	{
		if(spawn)
		{
			Enemy* pEnemy = Instantiate<Enemy>(this);
			pEnemy->SetPosition(XMFLOAT3{ (float)c * 5,0,0 });
		}
	}
	spawn = false;
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
