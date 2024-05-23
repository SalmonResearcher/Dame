#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class CharacterDisplay :public GameObject
{
private:
	Text* pText;

	int kill_;
	int jewel_;
	int score_;

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