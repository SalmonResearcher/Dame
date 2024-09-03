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
	int timer = 0;
	int count = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	XMFLOAT3 spawnPoint(0.0f, 0.0f, -50.0f);

	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;
	JewelBox* pBox;
	CharacterDisplay* pDisplay_;
	EnemySpawn* pEnemySpawn;
	JewelBullet* pBullet;

	float pitch = 1.0;
}

//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),hBGM_(-1),hScoreSound_(-1)
{
}

//������
void PlayScene::Initialize()
{
	hBGM_ = Audio::Load("SE/PlayScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_,false,1.0f,Global::MUSIC_VOLUME);

	hScoreSound_ = Audio::Load("SE/CountUp.wav", false);
	assert(hScoreSound_ >= 0);

	pPlayer = Instantiate<Player>(this);
	pStage = Instantiate<Stage>(this);
	pJewel = Instantiate<Jewel>(this);
	pBox = Instantiate<JewelBox>(this);
	pEnemySpawn = Instantiate<EnemySpawn>(this);
	pBullet = Instantiate<JewelBullet>(this);

	pBullet->BulletPosition(XMFLOAT3(INITAL_BULLET_POSITION,0,0));

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
	pEnemySpawn->SetSpawnPoint(spawnPoint);
	pEnemySpawn->SetRandomX(SPAWN_RANDOM_X_MIN, SPAWN_RANDOM_X_MAX);
	pEnemySpawn->StartSpawn();
}

//�X�V
void PlayScene::Update()
{
	count++;

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
		pitch += PITCH_INCREMENT;
	}
	else {
		pitch = INITIAL_PITCH;
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
	if (soundtimer % interval == 0) {
		Audio::Play(handle, true,pitch,COUNT_VOLUME);
	}
	soundtimer++;
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