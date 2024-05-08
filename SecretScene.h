#pragma once
#include "Engine/GameObject.h"
class SecretScene :public GameObject
{
private:
	int hModel_;
	int countDown;

	public:

		//コンストラクタ
		//引数：parent  親オブジェクト（SceneManager）
		SecretScene(GameObject* parent);

		//初期化
		void Initialize() override;

		//更新
		void Update() override;

		//描画
		void Draw() override;

		//開放
		void Release() override;

};



