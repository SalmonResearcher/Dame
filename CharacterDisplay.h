#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Score;

class CharacterDisplay :public GameObject
{
private:
	Text* pText_;
	Score* pScore_;
	int curScore_ = 0;    // 1フレーム前のスコア
	int score_ = 0;       // 現在のスコア
	int up_ = 0;          // 表示用スコア
	int kill_ = 0;        // プレイヤーが倒した敵の数
	int jewel_ = 0;       // プレイヤーが集めた宝石の数
	int bulletScore_ = 0; // 特定のスコア
	int incrementSteps_ = 10; // スコアを分割して加算する回数
	int incrementValue_ = 0; // スコアの増加量

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CharacterDisplay(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};