#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class JewelBullet :public GameObject
{
private:
	Text* pText;

	int kill_;
	int score_ = 0;


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	JewelBullet(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};