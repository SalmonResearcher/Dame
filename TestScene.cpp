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

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
