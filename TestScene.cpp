#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "Enemy/BossSlime/Boss_Fafrotskies.h"
#include "JewelBox.h"
#include "CharacterDisplay.h"


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
	Fafro* pFaf = Instantiate<Fafro>(this);
	pBox = Instantiate<JewelBox>(this);
	pDisplay = Instantiate<CharacterDisplay>(this);

	pText = new Text;
	pText->Initialize();

}

//更新
void TestScene::Update()
{

		if (count % 60 == 0)
		{
			Jewel* pJewel = Instantiate<Jewel>(this);
		}

		if (count % 30 == 0)
		{
		//	pEnemy = Instantiate<Enemy>(this);

		}

		count++;

		jewel_ = pBox->ReturnJewel();
		killCount_ = pPlayer->GetKillCount();
		score_ = (jewel_ * 200) + (killCount_ * 25);

}

//描画
void TestScene::Draw()
{
	pText->Draw(30, 30, score_);

}

//開放
void TestScene::Release()
{
}
