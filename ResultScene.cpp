#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Global.h"
//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//初期化
void ResultScene::Initialize()
{
	pDisp1_ = Instantiate<CharacterDisplay>(this);
	pDisp2_ = Instantiate<CharacterDisplay>(this);
	pDisp3_ = Instantiate<CharacterDisplay>(this);
	pDisp4_ = Instantiate<CharacterDisplay>(this);

	killCount_ = Global::GetKillCount();
	jewel_ = Global::GetJewel();
	jewelKill_ = Global::GetJewelKill();

	lastScore_ = ((jewel_ * 200) * 1.05) + ((jewelKill_) * ((killCount_ * 25) * 1.03));

	pDisp1_->ScorePosition(800, 40, true);
	pDisp2_->ScorePosition(800, 60, true);
	pDisp3_->ScorePosition(800, 80, true);
	pDisp4_->ScorePosition(800, 100, true);



	pDisp1_->TimerPosition(0, 0, false);
	pDisp2_->TimerPosition(0, 0, false);
	pDisp3_->TimerPosition(0, 0, false);
	pDisp4_->TimerPosition(0, 0, false);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	pDisp1_->Draw(killCount_);
	pDisp2_->Draw(jewel_);
	pDisp3_->Draw(jewelKill_);
	pDisp4_->Draw(lastScore_);
}

//開放
void ResultScene::Release()
{
}