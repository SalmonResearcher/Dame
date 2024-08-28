#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"

#include "Global.h"

namespace {

}

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//初期化
void ResultScene::Initialize()
{
	hImage_ = Image::Load("Result.png");
	assert(hImage_ >= 0);

	hCountSound_ = Audio::Load("SE/CountUp.wav", false);
	assert(hCountSound_ >= 0);

	hMoneySound_ = Audio::Load("SE/money.wav", false);
	assert(hMoneySound_ >= 0);

	hBGM_ = Audio::Load("SE/Result.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_,false,1.0f,Global::MUSIC_VOLUME);

	trPict_.position_ = XMFLOAT3(0, 0, 0);

	pDisp_ = Instantiate<CharacterDisplay>(this);

	killCount_ = Global::GetKillCount();
	jewel_ = Global::GetJewel();
	jewelKill_ = Global::GetJewelKill();

	//合計スコア＝（納品数*200）+（宝石キルスコア）*（100％ +（敵を倒した数*1％））
	totalScore_ = (killCount_ * 25)+(jewel_ * 200) + jewelKill_ * (1 + (killCount_ * 0.01));


	pDisp_->CreateScores(4);

	pDisp_->SetScoreValue(0, killCount_);
	pDisp_->SetScorePosition(0, 780, 200);
	pDisp_->SetScoreIncrementStep(0, 30);
	if (killCount_ < 30 && killCount_ != 0){
		pDisp_->SetScoreIncrementStep(0, killCount_);
	}

	pDisp_->SetScoreValue(1, jewel_);
	pDisp_->SetScorePosition(1, 780, 335);
	pDisp_->SetScoreIncrementStep(1, 30);
		if (jewel_ < 30 && jewel_ != 0){
		pDisp_->SetScoreIncrementStep(1, jewel_);
	}

	pDisp_->SetScoreValue(2, jewelKill_);
	pDisp_->SetScorePosition(2, 780, 470);
	pDisp_->SetScoreIncrementStep(2, 30);
	if (jewelKill_ < 30 && jewelKill_ != 0) {
		pDisp_->SetScoreIncrementStep(2, jewelKill_);
	}

	pDisp_->SetScoreValue(3, totalScore_);
	pDisp_->SetScorePosition(3, 780, 605);
	pDisp_->SetScoreIncrementStep(3, 120);
	if (totalScore_ < 120 && totalScore_ != 0) {
		pDisp_->SetScoreIncrementStep(3, totalScore_);
	}



}

//更新
void ResultScene::Update()
{
	switch (showScoreTime)
	{
	case 30:
		pDisp_->ScoreCountStart(0);
		countStart[0] = true;
		break;
	case 90:
		Audio::Play(hCountSound_, false,1.0,Global::SE_VOLUME);

		pDisp_->ScoreCountStart(1);
		countStart[1] = true;


		break;
	case 150:
		Audio::Play(hCountSound_, false, 1.0, Global::SE_VOLUME);

		pDisp_->ScoreCountStart(2);
		countStart[2] = true;


		break;

	case 240:
		countStart[3] = true;
		pDisp_->ScoreCountStart(3);
		break;

	default:
		break;
	}

	if (!pDisp_->IsCountEnd(0) && countStart[0])
	{
		SoundPlay(hCountS6ound_, 5);
	}

	if (!pDisp_->IsCountEnd(1) && countStart[1])
	{
		SoundPlay(hCountSound_, 5);
	}

	if (!pDisp_->IsCountEnd(2) && countStart[2])
	{
		SoundPlay(hCountSound_, 5);
	}

	if (!pDisp_->IsCountEnd(3) && countStart[3])
	{
		SoundPlay(hCountSound_, 5);
	}

	if (pDisp_->IsCountEnd(3) && !countEnd)
	{
		Audio::Play(hMoneySound_,false,1.0f,Global::SE_VOLUME);
		countEnd = true;
	}


	showScoreTime++;

	if (showScoreTime > 360 && Input::IsKey(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
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

void ResultScene::SoundPlay(int  handle, int interval)
{
	if (soundtimer % interval == 0) {
		Audio::Play(handle, true,1.0f,Global::SE_VOLUME);
	}
	soundtimer++;
}

void ResultScene::SoundStop(int handle)
{
}
