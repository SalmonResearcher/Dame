#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	short hImage_;
	CharacterDisplay* pDisplay_;

	int score_;

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

};

