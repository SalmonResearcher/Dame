#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "Enemy/BossSlime/Boss_Fafrotskies.h"

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
	Enemy* pEnemy = Instantiate<Enemy>(this);
	Fafro* pFaf = Instantiate<Fafro>(this);

}

//�X�V
void TestScene::Update()
{
	//if (((timer %35== 0) && count < 1))
	//{
	//	count++;
	//}

	//	timer++;
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
