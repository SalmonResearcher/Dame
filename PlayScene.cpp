#include "PlayScene.h"
#include "Global.h"

#include "Player.h"
#include "Stage.h"
#include "Enemy.h"
#include "Jewel.h"
#include "JewelBox.h"
#include "JewelBullet.h"
#include "CharacterDisplay.h"

#include "EnemySpawn.h"

#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"

namespace {
	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;
	JewelBox* pBox;
	CharacterDisplay* pDisplay_;
	EnemySpawn* pEnemySpawn;
	JewelBullet* pBullet;
}

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),hBGM_(-1),hScoreSound_(-1),
	pitch_(1.0f),timer_(0),count_(0),jewel_(0),killCount_(0)
{
}

//������
void PlayScene::Initialize()
{
	hBGM_ = Audio::Load("Sounds/BGM/PlayScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_,false,INITIAL_PITCH,Global::MUSIC_VOLUME);

	hScoreSound_ = Audio::Load("Sounds/SE/CountUp.wav", false);
	assert(hScoreSound_ >= 0);

	//�Ăяo��
	pPlayer = Instantiate<Player>(this);
	pStage = Instantiate<Stage>(this);
	pBox = Instantiate<JewelBox>(this);
	pEnemySpawn = Instantiate<EnemySpawn>(this);
	pBullet = Instantiate<JewelBullet>(this);
	pJewel = Instantiate<Jewel>(this);

	pBullet->BulletPosition(INITAL_POSITION_X,0.0f,0.0f);
	pJewel->SetPosition(INITAL_POSITION_X,0.0f,0.0f);
	pJewel->KillMe();
	pDisplay_ = Instantiate<CharacterDisplay>(this);

	// �W���G���A�X�R�A�A�^�C�}�[�̏����ݒ�
	pDisplay_->CreateJewels(INITIAL_UI);
	pDisplay_->CreateScores(INITIAL_UI);
	pDisplay_->CreateTimers(INITIAL_UI);

	// �W���G���A�X�R�A�A�^�C�}�[�̈ʒu�ݒ�
	pDisplay_->SetJewelPosition(JEWEL_INDEX, JEWEL_POSITION_X, JEWEL_POSITION_Y);
	pDisplay_->SetScorePosition(SCORE_INDEX, SCORE_POSITION_X, SCORE_POSITION_Y);
	pDisplay_->SetTimerPosition(TIMER_INDEX, TIMER_POSITION_X, TIMER_POSITION_Y);

	// �X�R�A�J�E���g�J�n
	pDisplay_->ScoreCountStart(SCORE_INDEX);

	// �^�C�}�[�ݒ�ƊJ�n
	pDisplay_->SetTimerLimit(TIMER_INDEX, TIMER_LIMIT_SECONDS);
	pDisplay_->TimerStart(TIMER_INDEX);

	// �G�̃X�|�[���ݒ�
	pEnemySpawn->SetInterval(ENEMY_SPAWN_INTERVAL);
	pEnemySpawn->SetSpawnPoint(SPAWN_POINT);
	pEnemySpawn->SetRandomX(SPAWN_RANDOM_X_MIN, SPAWN_RANDOM_X_MAX);
	pEnemySpawn->StartSpawn();
}

//�X�V
void PlayScene::Update()
{
	count_++;

	// ���݂̃W���G���ƃL���J�E���g���擾
	jewel_ = pBox->ReturnJewel();
	killCount_ = pPlayer->GetKillCount();

	// �^�C�}�[��0�ɂȂ邩
	if (pDisplay_->IsFinished(SCORE_INDEX)) {
		HandleEndOfGame();
	}

	// �X�R�A�v�Z
	pDisplay_->CalcScoreValue(SCORE_INDEX);

	// �X�R�A�J�E���g���I�����Ă��Ȃ��ꍇ�̏���
	if (!pDisplay_->IsCountEnd(SCORE_INDEX)) {
		SoundPlay(hScoreSound_, SOUND_PRIORITY);
		pitch_ += PITCH_INCREMENT;
	}
	else {
		pitch_ = INITIAL_PITCH;
	}
}

//�`��
void PlayScene::Draw()
{
	pDisplay_->Draw();

}

//�J��
void PlayScene::Release()
{
}

void PlayScene::SoundPlay(int  handle, int interval)
{
	if (soundtimer_ % interval == 0) {
		Audio::Play(handle, true,pitch_,COUNT_VOLUME);
	}
	soundtimer_++;
}

// �Q�[���I�����̏���
void PlayScene::HandleEndOfGame()
{
	pEnemySpawn->StopSpawn();

	Global::AddJewel(jewel_);
	Global::AddKillCount(killCount_);

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT);
}