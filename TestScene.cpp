#include "TestScene.h"
#include "Global.h"

#include "Player.h"
#include "Stage.h"
#include "Enemy/Enemy.h"
#include "Jewel.h"
#include "Enemy/BossSlime/Boss_Fafrotskies.h"
#include "JewelBox.h"
#include "CharacterDisplay.h"
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

	pPlayer_ = Instantiate<Player>(this);
	pStage_ = Instantiate<Stage>(this);
	pJewel_ = Instantiate<Jewel>(this);
	Fafro* pFaf = Instantiate<Fafro>(this);
	pBox_ = Instantiate<JewelBox>(this);
	pDisplay_ = Instantiate<CharacterDisplay>(this);

	pText_ = new Text;
	pText_->Initialize();
	pDisplay_->SetScorePosition(900, 5);
	pDisplay_->SetTimerPosition(850, 5);
}

//更新
void TestScene::Update()
{
	
		if (count_ % 60 == 0)
		{
			Jewel* pJewel_ = Instantiate<Jewel>(this);
		}

		if (Input::IsKeyDown(DIK_P))
		{
			pEnemy_ = Instantiate<Enemy>(this);

		}

		count_++;

		jewel_ = pBox_->ReturnJewel();
		killCount_ = pPlayer_->GetKillCount();

		if (Input::IsKeyDown(DIK_C)) {
			Global::SetScore(pDisplay_->GetScore());
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_RESULT);

		}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
