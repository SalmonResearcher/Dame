#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "Enemy/BossSlime/Boss_Fafrotskies.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	pPlayer = Instantiate<Player>(this);
	pStage = Instantiate<Stage>(this);
	pJewel = Instantiate<Jewel>(this);
	Enemy* pEnemy = Instantiate<Enemy>(this);
	Fafro* pFaf = Instantiate<Fafro>(this);

}

//更新
void TestScene::Update()
{
	//if (((timer %35== 0) && count < 1))
	//{
	//	count++;
	//}

	//	timer++;
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
