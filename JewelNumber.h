#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class JewelNumber :public GameObject
{
private:
	int jewel_= 0;
	Text* pText_;

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

	void Draw(int _x, int _y);

	//開放
	void Release() override;
};