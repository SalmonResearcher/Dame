#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	int hImage_;
	int hCountSound_;
	int hMoneySound_;

	int hBGM_;

	float pitch_;

	CharacterDisplay* pDisp_;

	int killCount_;
	int jewel_;
	int jewelKill_;

	int totalScore_;
	int showScoreTime;

	int soundtimer;

	bool countStart[4];

	bool countEnd = false;

	int currentCaseIndex; // 現在のケースを追跡する変数


	//スコア表示時の定数たち
	enum ScoreCountTimes
	{
		START_SCORE_COUNT_0 = 30,
		START_SCORE_COUNT_1 = 90,
		START_SCORE_COUNT_2 = 150,
		START_SCORE_COUNT_3 = 240,
		MAX_SHOW_SCORE_TIME = 360,
		SOUND_PLAY_INTERVAL = 5
	};

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SoundPlay(int handle,int interval);

	void SoundStop(int handle);

};

