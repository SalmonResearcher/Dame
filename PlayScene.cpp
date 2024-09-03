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

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),hBGM_(-1),hScoreSound_(-1)
{
}

//初期化
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

	// ジュエル、スコア、タイマーの初期設定
	pDisplay_->CreateJewels(INITIAL_UI);
	pDisplay_->CreateScores(INITIAL_UI);
	pDisplay_->CreateTimers(INITIAL_UI);

	// ジュエル、スコア、タイマーの位置設定
	pDisplay_->SetJewelPosition(JEWEL_INDEX, JEWEL_POSITION_X, JEWEL_POSITION_Y);
	pDisplay_->SetScorePosition(SCORE_INDEX, SCORE_POSITION_X, SCORE_POSITION_Y);
	pDisplay_->SetTimerPosition(TIMER_INDEX, TIMER_POSITION_X, TIMER_POSITION_Y);

	// スコアカウント開始
	pDisplay_->ScoreCountStart(SCORE_INDEX);

	// タイマー設定と開始
	pDisplay_->SetTimerLimit(TIMER_INDEX, TIMER_LIMIT_SECONDS);
	pDisplay_->TimerStart(TIMER_INDEX);

	// 敵のスポーン設定
	pEnemySpawn->SetInterval(ENEMY_SPAWN_INTERVAL);
	pEnemySpawn->SetSpawnPoint(spawnPoint);
	pEnemySpawn->SetRandomX(SPAWN_RANDOM_X_MIN, SPAWN_RANDOM_X_MAX);
	pEnemySpawn->StartSpawn();
}

//更新
void PlayScene::Update()
{
	count++;

	// 現在のジュエルとキルカウントを取得
	jewel_ = pBox->ReturnJewel();
	killCount_ = pPlayer->GetKillCount();

	// タイマーが0になるか
	if (pDisplay_->IsFinished(SCORE_INDEX)) {
		HandleEndOfGame();
	}

	// スコア計算
	pDisplay_->CalcScoreValue(SCORE_INDEX);

	// スコアカウントが終了していない場合の処理
	if (!pDisplay_->IsCountEnd(SCORE_INDEX)) {
		SoundPlay(hScoreSound_, SOUND_PRIORITY);
		pitch += PITCH_INCREMENT;
	}
	else {
		pitch = INITIAL_PITCH;
	}
}

//描画
void PlayScene::Draw()
{
	pDisplay_->Draw();

}

//開放
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

// ゲーム終了時の処理
void PlayScene::HandleEndOfGame()
{
	pEnemySpawn->StopSpawn();

	Global::AddJewel(jewel_);
	Global::AddKillCount(killCount_);

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT);
}