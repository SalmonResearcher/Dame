#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



//テストシーンを管理するクラス
class TestScene : public GameObject
{
	int hBGM_;

	int hScoreSound_;
	int soundtimer;
	Text* pText;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//サウンドを〇Fごとに再生する
	void SoundPlay(int handle, int interval);

};