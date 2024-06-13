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
	hImage_ = Image::Load("Result.png");
	trPict_.position_ = XMFLOAT3(0, 0, 0);

	pDisp_ = Instantiate<CharacterDisplay>(this);

	killCount_ = Global::GetKillCount();
	jewel_ = Global::GetJewel();
	jewelKill_ = Global::GetJewelKill();

	//合計スコア＝（納品数*200）+（宝石キルスコア）*（100％ +（敵を倒した数*1％））
	totalScore_ = (killCount_ * 25)+(jewel_ * 200) + jewelKill_ * (1 + (killCount_ * 0.01));


	pDisp_->CreateScores(4);

	pDisp_->SetScoreValue(0, killCount_);
	pDisp_->SetScorePosition(0, 400, 400);

	pDisp_->SetScoreValue(1, jewel_);
	pDisp_->SetScorePosition(1, 400, 400);

	pDisp_->SetScoreValue(2, jewelKill_);
	pDisp_->SetScorePosition(2, 400, 400);

	pDisp_->SetScoreValue(3, totalScore_);
	pDisp_->SetScorePosition(3, 400, 400);


}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	Image::SetTransform(hImage_, trPict_);
	Image::Draw(hImage_);

	pDisp_->Draw();

}

//開放
void ResultScene::Release()
{
}