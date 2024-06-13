#include "TestScene.h"
#include "Global.h"

#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "Enemy/BossSlime/Boss_Fafrotskies.h"
#include "JewelBox.h"
#include "CharacterDisplay.h"
#include "Score.h"

#include "Engine/SceneManager.h"

#include "Engine/Input.h"


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

	pDisplay->CreateJewels(1);
	pDisplay->CreateScores(1);
	pDisplay->CreateTimers(1);

	pDisplay->SetJewelPosition(0, 45, 400);

}

//更新
void TestScene::Update()
{
		if (count % 30 == 0)
		{
			Jewel* pJewel = Instantiate<Jewel>(this);
		}

		if (Input::IsKeyDown(DIK_P))
		{
			pEnemy = Instantiate<Enemy>(this);

		}

		count++;



		jewel_ = pBox->ReturnJewel();
		killCount_ = pPlayer->GetKillCount();

		

		if (Input::IsKeyDown(DIK_C)) {
			Global::AddJewel(jewel_);
			Global::AddKillCount(killCount_);

			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_RESULT);

		}
		pDisplay->SetScoreValue(0);

}

//描画
void TestScene::Draw()
{
	pDisplay->Draw();
}

//開放
void TestScene::Release()
{
}
