#pragma once
#include "Engine/GameObject.h"

class Player;
class Stage;
class Jewel;
class Enemy;
//テストシーンを管理するクラス
class TestScene : public GameObject
{
	bool spawn = true;
	int timer = 0;
	int count = 0;

	Player* pPlayer;
	Stage* pStage;
	Jewel* pJewel;
	Enemy* pEnemy;

	Transform tjewel_;


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
};