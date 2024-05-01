#pragma once
#include "Engine/GameObject.h"

#include "Engine/Text.h"

#include <string.h>

class StageSelectScene :
    public GameObject
{
private:
	Text* pText;

	enum
	{
		STAGE1,
		STAGE2,
		STAGE3,
		MAX_STAGE
	};

	int hStage_[MAX_STAGE];
	Transform trStage[MAX_STAGE];	//ステージプレビューのトランスフォーム
	
	int hImage_[2];
	Transform trImage_[2];

	XMFLOAT3 cameraPos;
	float moveX;

	int hSkysphere;
	Transform trSky;

	std::string name = "MiniStage";
	std::string num;
	std::string ext = ".fbx";

	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };

	//回転用の時間
	float timer;

	//縦揺れ時間
	float yMoveTime;

	//ゆっくり上下させたい
	float sinwave;

	//ステージ選択するときのカウント
	int selectCount = 0;

	bool flg = false;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StageSelectScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//プレビューのサイズを変更。trueで大きく、faseで小さくなる
	void StageScaling(Transform* stage_, bool big);

	void StageScaling(Transform* stage_, bool big , float rate);

};

