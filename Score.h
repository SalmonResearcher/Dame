#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class Score :public GameObject
{
private:
	Text* pText_;

	int curScore_ = 0;    // 1フレーム前のスコア
	int score_ = 0;       // 現在のスコア
	int up_ = 0;          // 表示用スコア
	int kill_ = 0;        // プレイヤーが倒した敵の数
	int jewel_ = 0;       // プレイヤーが集めた宝石の数
	int bulletScore_ = 0; // 特定のスコア
	int incrementSteps_ = 25; // スコアを分割して加算する回数
	int incrementValue_ = 0; // スコアの増加量

	int saveScore_ = 0;
	int posX_, posY_;

	bool countUp_ = false;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Score(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	
	int GetScore() {return saveScore_;}
	void SetScore(int score) { score_ = score; }
	void SetDisplayPosition(int x, int y) { posX_ = x; posY_ = y; }

	void ScoreCaluc();
	void Start() { countUp_ = true; }
	void Stop() { countUp_ = false; }
	void SetIncrementSteps(int step) { incrementSteps_ = step; }
};