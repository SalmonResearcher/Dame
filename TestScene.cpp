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
	if (FindObject("Jewel") == nullptr)
	{
		if (count % 60 == 0)
		{
			Instantiate<Jewel>(this);

		}
		count++;
	}
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
