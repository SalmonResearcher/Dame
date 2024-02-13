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
	
	if (((timer %1 == 0) && count < 80))
	{
		Enemy* pEnemy = Instantiate<Enemy>(this);
		count++;
	}

		timer++;
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
