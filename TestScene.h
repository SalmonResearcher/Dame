#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Player;
class Stage;
class Jewel;
class Enemy;
class JewelBox;
class CharacterDisplay;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	bool spawn_ = true;
	int timer_ = 0;
	int count_ = 0;

	int jewel_;
	int killCount_;
	int score_ = 0;

	Player* pPlayer_;
	Stage* pStage_;
	Jewel* pJewel_;
	Enemy* pEnemy_;
	JewelBox* pBox_;
	CharacterDisplay* pDisplay_;

	Text* pText_;

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