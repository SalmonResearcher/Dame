#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

enum ENEMIES {
	SLIME = 0,
	B_SLIME
};

class EnemySpawnPoint :public GameObject
{
private:
	//std::vector<std::vector<float>> spawner; // 敵の湧き位置を管理する二次元配列
	struct Rect {
		float up = 1;
		float down = 1;
	};
	Rect point;


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	EnemySpawnPoint(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetSpawnPoint(float vertical, float beside);
	void SetPosition(XMFLOAT3 _pos)
	{
		transform_.position_ = _pos;
	}

	//スポーン間隔（ランダムで+-10Fでもいいかも）
	void SetSpawnInterval(float interval);

	void SpawnPointChange();

};