#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"
#include "Jewel.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	pPlayer = Instantiate<Player>(this);
	pStage = Instantiate<Stage>(this);
	pJewel = Instantiate<Jewel>(this);
}

//�X�V
void TestScene::Update()
{
	
	if (((timer %60 == 0) && count < 80))
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
