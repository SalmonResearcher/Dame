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

		if (Input::IsKeyDown(DIK_P))
		{
			pEnemy = Instantiate<Enemy>(this);

		}

		count++;

		jewel_ = pBox->ReturnJewel();
		killCount_ = pPlayer->GetKillCount();

		if (Input::IsKeyDown(DIK_C)) {
			Global::SetJewel(jewel_);
			Global::SetKillCount(killCount_);
			
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
