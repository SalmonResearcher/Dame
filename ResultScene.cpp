#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
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

	pDisp1_ = Instantiate<CharacterDisplay>(this);
	pDisp2_ = Instantiate<CharacterDisplay>(this);
	pDisp3_ = Instantiate<CharacterDisplay>(this);
	pDisp4_ = Instantiate<CharacterDisplay>(this);

	killCount_ = Global::GetKillCount();
	jewel_ = Global::GetJewel();
	jewelKill_ = Global::GetJewelKill();

	//���v�X�R�A���i�[�i��*200�j+�i��΃L���X�R�A�j*�i100�� +�i�G��|������*5���j�j
	totalScore_ = (jewel_ * 200) + jewelKill_ * (1 + (killCount_ * 0.05)) + (killCount_ * 25);


	pDisp1_->ScorePosition(800, 80);
	pDisp2_->ScorePosition(800, 200);
	pDisp3_->ScorePosition(800, 320);
	pDisp4_->ScorePosition(800, 460);

	pDisp1_->HideTimer();
	pDisp2_->HideTimer();
	pDisp3_->HideTimer();
	pDisp4_->HideTimer();	
	
	pDisp1_->HideScore();
	pDisp2_->HideScore();
	pDisp3_->HideScore();
	pDisp4_->HideScore();



}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
	pDisp1_->Draw(killCount_);
	pDisp2_->Draw(jewel_);
	pDisp3_->Draw(jewelKill_);
	pDisp4_->Draw(totalScore_);

	Image::SetTransform(hImage_, trPict_);
	Image::Draw(hImage_);
}

//�J��
void ResultScene::Release()
{
}