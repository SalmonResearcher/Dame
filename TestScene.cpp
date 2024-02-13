#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Player* pPlayer = Instantiate<Player>(this);
	Stage* pStage = Instantiate<Stage>(this);


}

//更新
void TestScene::Update()
{
	
	if (((timer %1 == 0) && count < 80))
	{
		Enemy* pEnemy = Instantiate<Enemy>(this);
		count++;
	}

		timer++;
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
