#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"

#include "Global.h"
//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//������
void ResultScene::Initialize()
{
	hImage_ = Image::Load("Result.png");
	trPict_.position_ = XMFLOAT3(0, 0, 0);

	pDisp_ = Instantiate<CharacterDisplay>(this);

	killCount_ = Global::GetKillCount();
	jewel_ = Global::GetJewel();
	jewelKill_ = Global::GetJewelKill();

	//���v�X�R�A���i�[�i��*200�j+�i��΃L���X�R�A�j*�i100�� +�i�G��|������*1���j�j
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

//�X�V
void ResultScene::Update()
{
	switch (showScoreTime)
	{
	case 0:
		pDisp_->ScoreCountStart(0);
		break;
	case 60:
		pDisp_->ScoreCountStart(1);

		break;
	case 120:
		pDisp_->ScoreCountStart(2);

		break;
	case 210:
		pDisp_->ScoreCountStart(3);

		break;
	default:
		break;
	}


	showScoreTime++;

	if (showScoreTime >= 210) {
		if (Input::IsKeyDown(DIK_SPACE)) { 
			pDisp_->SetScoreIncrementStep(3, 1);
		}
	}

	else if (showScoreTime >= 120) {
		if (Input::IsKeyDown(DIK_SPACE)) { 
			pDisp_->SetScoreIncrementStep(2, 1);
			showScoreTime = 210;
		}
	}
	else if (showScoreTime >= 60) {
		if (Input::IsKeyDown(DIK_SPACE)) { 
			pDisp_->SetScoreIncrementStep(1, 1);
			showScoreTime = 120;
		}
	}
	else if (showScoreTime >= 0) {
		if (Input::IsKeyDown(DIK_SPACE)) { 
			pDisp_->SetScoreIncrementStep(0, 1); 
			showScoreTime = 60;
		}
	}
}

//�`��
void ResultScene::Draw()
{
	Image::SetTransform(hImage_, trPict_);
	Image::Draw(hImage_);

	pDisp_->Draw();

}

//�J��
void ResultScene::Release()
{
}