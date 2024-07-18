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
		MAX_IMAGE
	};

	int hImage_[MAX_IMAGE];
	Transform trImage_[MAX_IMAGE];

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

