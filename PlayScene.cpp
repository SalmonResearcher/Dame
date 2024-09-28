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

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"),hBGM_(-1),hScoreSound_(-1),
	pitch_(1.0f),timer_(0),count_(0),jewel_(0),killCount_(0)
{
}

//初期化
void PlayScene::Initialize()
{
	hBGM_ = Audio::Load("Sounds/BGM/PlayScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_,false,INITIAL_PITCH,Global::MUSIC_VOLUME);

	hScoreSound_ = Audio::Load("Sounds/SE/CountUp.wav", false);
	assert(hScoreSound_ >= 0);

	//呼び出し
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
	pEnemySpawn->SetSpawnPoint(SPAWN_POINT);
	pEnemySpawn->SetRandomX(SPAWN_RANDOM_X_MIN, SPAWN_RANDOM_X_MAX);
	pEnemySpawn->StartSpawn();
}

//更新
void PlayScene::Update()
{
	count_++;

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
		pitch_ += PITCH_INCREMENT;
	}
	else {
		pitch_ = INITIAL_PITCH;
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
	if (soundtimer_ % interval == 0) {
		Audio::Play(handle, true,pitch_,COUNT_VOLUME);
	}
	soundtimer_++;
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