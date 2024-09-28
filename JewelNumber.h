#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class JewelNumber :public GameObject
{
private:
	int jewel_= 0;
	Text* pText_;

	int posX_,posY_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	JewelNumber(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetJewelPosition(int x, int y) { posX_ = x; posY_ = y; }
	void SetJewelNumber(int value) { jewel_ = value; }
};