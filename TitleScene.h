#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class TitleScene :public GameObject
{
private:

	int hBGM_;

	enum
	{
		BG,
		SLIME,
		GROUND,
		HUMAN,
		LOGO,
		PRESS,
		MAX_IMAGE
	};

	int hImage_[MAX_IMAGE];
	Transform trImage_[MAX_IMAGE];

	//揺れる量
	float frequency_;

	//大きさが最大になるまでの速度
	const float SCALE_SPEED = 0.05f;

	//最大の大きさ
	const float MAX_SCALE = 0.05f;

	//振れ幅が最大になるまでの速度
	const float SWAY_SPEED = 0.5f;
	const float HUMAN_SWAY_SPEED = 2.0f;

	//振れ幅の大きさ
	const float SWAY_AMPLITUDE = 0.05f;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

