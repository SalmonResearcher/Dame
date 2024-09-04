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

	hCountSound_ = Audio::Load("Sounds/SE/CountUp.wav", false);
	assert(hCountSound_ >= 0);

	hMoneySound_ = Audio::Load("Sounds/SE/money.wav", false);
	assert(hMoneySound_ >= 0);

	hBGM_ = Audio::Load("Sounds/BGM/Result.wav", true);
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
	if (jewel_ >= MAX_SCORE)
	{
		jewel_ = MAX_SCORE;
	}
	if (jewelKill_ >= MAX_SCORE)
	{
		jewelKill_ = MAX_SCORE;
	}



	baseJewelScore = Global::GetJewelScore();
	baseKillScore = Global::GetKillScore();

	//���v�X�R�A���i�[�i��*200�j+�i��΃L���X�R�A�j*�i100�� +�i�G��|������*1���j�j
	totalScore_ = (killCount_ * baseKillScore)+(jewel_ * baseJewelScore) + jewelKill_ * (1 + (killCount_ * 0.01));

	if (totalScore_ >= MAX_SCORE) {
		totalScore_ = MAX_SCORE;
	}


	pDisp_->CreateScores(MAX_DISPLAY);

pDisp_->SetScoreValue(KILL_COUNT, killCount_);
pDisp_->SetScorePosition(KILL_COUNT, SCORE_POSITION_X, KILL_SCORE_POSITION_Y);
pDisp_->SetScoreIncrementStep(KILL_COUNT, DEFAULT_INCREMENT_STEP);
if (killCount_ < DEFAULT_SCORE_INCREMENT_FRAMES && killCount_ != 0) {
    pDisp_->SetScoreIncrementStep(KILL_COUNT, killCount_);
}

pDisp_->SetScoreValue(JEWEL_COUNT, jewel_);
pDisp_->SetScorePosition(JEWEL_COUNT, SCORE_POSITION_X, JEWEL_SCORE_POSITION_Y);
pDisp_->SetScoreIncrementStep(JEWEL_COUNT, DEFAULT_INCREMENT_STEP);
if (jewel_ < DEFAULT_SCORE_INCREMENT_FRAMES && jewel_ != 0) {
    pDisp_->SetScoreIncrementStep(JEWEL_COUNT, jewel_);
}

pDisp_->SetScoreValue(JEWEL_KILL_COUNT, jewelKill_);
pDisp_->SetScorePosition(JEWEL_KILL_COUNT, SCORE_POSITION_X, JEWEL_KILL_SCORE_POSITION_Y);
pDisp_->SetScoreIncrementStep(JEWEL_KILL_COUNT, DEFAULT_INCREMENT_STEP);
if (jewelKill_ < DEFAULT_SCORE_INCREMENT_FRAMES && jewelKill_ != 0) {
    pDisp_->SetScoreIncrementStep(JEWEL_KILL_COUNT, jewelKill_);
}

pDisp_->SetScoreValue(TOTAL_SCORE, totalScore_);
pDisp_->SetScorePosition(TOTAL_SCORE, SCORE_POSITION_X, TOTAL_SCORE_POSITION_Y);
pDisp_->SetScoreIncrementStep(TOTAL_SCORE, TOTAL_SCORE_INCREMENT_STEP);
if (totalScore_ < TOTAL_SCORE_INCREMENT_FRAMES && totalScore_ != 0) {
    pDisp_->SetScoreIncrementStep(TOTAL_SCORE, totalScore_);	}



}

void ResultScene::Update()
{
	// �X�y�[�X�L�[�������ꂽ�ꍇ�A���̃P�[�X�ɐi��
	if (Input::IsKeyDown(DIK_SPACE))
	{
		switch (currentCaseIndex)
		{
		case KILL_COUNT:
			showScoreTime = START_SCORE_COUNT_1; // ���̃P�[�X�̊J�n���Ԃɐݒ�
			pDisp_->InstantSyncScore(KILL_COUNT);

			break;
		case JEWEL_COUNT:
			showScoreTime = START_SCORE_COUNT_2;
			pDisp_->InstantSyncScore(JEWEL_COUNT);

			break;
		case JEWEL_KILL_COUNT:
			showScoreTime = START_SCORE_COUNT_3;
			pDisp_->InstantSyncScore(JEWEL_KILL_COUNT);

			break;
		case TOTAL_SCORE:
			showScoreTime = MAX_SHOW_SCORE_TIME; // �Ō�̃P�[�X���I�������̎���
			pDisp_->InstantSyncScore(TOTAL_SCORE);

			break;
		default:
			break;
		}
		currentCaseIndex++; // ���̃P�[�X�Ɉڍs
	}

	switch (showScoreTime)
	{
	case START_SCORE_COUNT_0:
		pDisp_->ScoreCountStart(KILL_COUNT);
		countStart[0] = true;
		currentCaseIndex = 1; // ���݂̃P�[�X���X�V
		break;

	case START_SCORE_COUNT_1:
		Audio::Play(hCountSound_, false, 1.0, Global::SE_VOLUME);
		pDisp_->ScoreCountStart(JEWEL_COUNT);
		countStart[1] = true;
		currentCaseIndex = 2;
		break;

	case START_SCORE_COUNT_2:
		Audio::Play(hCountSound_, false, 1.0, Global::SE_VOLUME);
		pDisp_->ScoreCountStart(JEWEL_KILL_COUNT);
		countStart[2] = true;
		currentCaseIndex = 3;
		break;

	case START_SCORE_COUNT_3:
		countStart[3] = true;
		pDisp_->ScoreCountStart(TOTAL_SCORE);
		currentCaseIndex = 4;
		break;

	default:
		break;
	}

	// �X�R�A�J�E���g���I�����Ă��Ȃ��ꍇ�A�����Đ�����
	for (int i = 0; i < MAX_DISPLAY; ++i)
	{
		if (!pDisp_->IsCountEnd(i) && countStart[i])
		{
			SoundPlay(hCountSound_, SOUND_PLAY_INTERVAL);
		}
	}

	// �S�ẴX�R�A�J�E���g���I�������ꍇ�̏���
	if (pDisp_->IsCountEnd(TOTAL_SCORE) && !countEnd)
	{
		Audio::Play(hMoneySound_, false, 1.0f, Global::SE_VOLUME);
		countEnd = true;
	}

	showScoreTime++;

	// �V�[����؂�ւ��邽�߂̃X�y�[�X�L�[�̌��m�i���ɐ؂�ւ��\�ȏ�ԂɂȂ��Ă���ꍇ�j
	if (pDisp_->IsCountEnd(TOTAL_SCORE) && Input::IsKeyDown(DIK_SPACE ))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
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
