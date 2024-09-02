#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"

#include "Global.h"

namespace {
	int baseJewelScore;
	int baseKillScore;

	const int MAX_SCORE = 999999;
}

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(-1), hCountSound_(-1), hMoneySound_(-1), hBGM_(-1), pitch_(1.0), killCount_(-1),
	jewel_(-1),jewelKill_(-1),totalScore_(-1),showScoreTime(0),soundtimer(0)
{
}

//������
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

	if (killCount_ >= MAX_SCORE)
	{
		killCount_ = MAX_SCORE;
	}

	baseJewelScore = Global::GetJewelScore();
	baseKillScore = Global::GetKillScore();

	//���v�X�R�A���i�[�i��*200�j+�i��΃L���X�R�A�j*�i100�� +�i�G��|������*1���j�j
	totalScore_ = (killCount_ * baseKillScore)+(jewel_ * baseJewelScore) + jewelKill_ * (1 + (killCount_ * 0.01));


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

void ResultScene::Update()
{
	// �X�y�[�X�L�[�������ꂽ�ꍇ�A���̃P�[�X�ɐi��
	if (Input::IsKeyDown(DIK_SPACE))
	{
		switch (currentCaseIndex)
		{
		case 0:
			showScoreTime = START_SCORE_COUNT_1; // ���̃P�[�X�̊J�n���Ԃɐݒ�
			pDisp_->InstantSyncScore(0);

			break;
		case 1:
			showScoreTime = START_SCORE_COUNT_2;
			pDisp_->InstantSyncScore(1);

			break;
		case 2:
			showScoreTime = START_SCORE_COUNT_3;
			pDisp_->InstantSyncScore(2);

			break;
		case 3:
			showScoreTime = MAX_SHOW_SCORE_TIME; // �Ō�̃P�[�X���I�������̎���
			pDisp_->InstantSyncScore(3);

			break;
		default:
			break;
		}
		currentCaseIndex++; // ���̃P�[�X�Ɉڍs
	}

	switch (showScoreTime)
	{
	case START_SCORE_COUNT_0:
		pDisp_->ScoreCountStart(0);
		countStart[0] = true;
		currentCaseIndex = 1; // ���݂̃P�[�X���X�V
		break;

	case START_SCORE_COUNT_1:
		Audio::Play(hCountSound_, false, 1.0, Global::SE_VOLUME);
		pDisp_->ScoreCountStart(1);
		countStart[1] = true;
		currentCaseIndex = 2;
		break;

	case START_SCORE_COUNT_2:
		Audio::Play(hCountSound_, false, 1.0, Global::SE_VOLUME);
		pDisp_->ScoreCountStart(2);
		countStart[2] = true;
		currentCaseIndex = 3;
		break;

	case START_SCORE_COUNT_3:
		countStart[3] = true;
		pDisp_->ScoreCountStart(3);
		currentCaseIndex = 4;
		break;

	default:
		break;
	}

	// �X�R�A�J�E���g���I�����Ă��Ȃ��ꍇ�A�����Đ�����
	for (int i = 0; i < 4; ++i)
	{
		if (!pDisp_->IsCountEnd(i) && countStart[i])
		{
			SoundPlay(hCountSound_, SOUND_PLAY_INTERVAL);
		}
	}

	// �S�ẴX�R�A�J�E���g���I�������ꍇ�̏���
	if (pDisp_->IsCountEnd(3) && !countEnd)
	{
		Audio::Play(hMoneySound_, false, 1.0f, Global::SE_VOLUME);
		countEnd = true;
	}

	showScoreTime++;

	// �V�[����؂�ւ��邽�߂̃X�y�[�X�L�[�̌��m�i���ɐ؂�ւ��\�ȏ�ԂɂȂ��Ă���ꍇ�j
	//if (pDisp_->IsCountEnd(3) && Input::IsKey(DIK_SPACE))
	//{
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_TITLE);
	//}
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

void ResultScene::SoundPlay(int  handle, int interval)
{
	if (soundtimer % interval == 0) {
		Audio::Play(handle, true,pitch_,Global::SE_VOLUME);
	}
	soundtimer++;
}

void ResultScene::SoundStop(int handle)
{
}
