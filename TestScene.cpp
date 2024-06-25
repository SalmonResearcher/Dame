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

namespace {
	bool spawn = true;
	int timer = 0;
	int count = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;
	JewelBox* pBox;
	CharacterDisplay* pDisplay;
}

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
	pBox = Instantiate<JewelBox>(this);
	pText = new Text;
	pText->Initialize();

	pDisplay = Instantiate<CharacterDisplay>(this);

	pDisplay->CreateJewels(1);
	pDisplay->CreateScores(1);
	pDisplay->CreateTimers(1);

	pDisplay->SetJewelPosition(0, 45, 650);
	pDisplay->SetScorePosition(0, 950, 45);
	pDisplay->SetTimerPosition(0, 850, 45);

	pDisplay->ScoreCountStart(0);

	pDisplay->SetTimerLimit(0, 30);
	pDisplay->TimerStart(0);
}

//更新
void TestScene::Update()
{


		if (count % 30 == 0)
		{
			
		}

		if (Input::IsKeyDown(DIK_P))
		{
			pEnemy = InstantiateFront<Enemy>(this);

		}

		count++;



		jewel_ = pBox->ReturnJewel();
		killCount_ = pPlayer->GetKillCount();

		

		if (Input::IsKeyDown(DIK_C) || pDisplay->IsFinished(0)) {
			Global::AddJewel(jewel_);
			Global::AddKillCount(killCount_);

			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_RESULT);
		}
		pDisplay->CalcScoreValue(0);
		

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
