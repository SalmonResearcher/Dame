#pragma once
#include "Engine/GameObject.h"




class StageSelectScene :
    public GameObject
{
private:

	enum
	{
		STAGE1,
		STAGE2,
		MAX_STAGE
	};


	int hBGM_;
	int hImage_[2];
	int hStage_[MAX_STAGE];

	Transform trStage[MAX_STAGE];	//ステージプレビューのトランスフォーム
	Transform trImage_[2];


	//ステージ選択するときのカウント
	int selectCount = 0;

	//そのステージで止まったかどうか
	bool isStageStop = false;

	XMFLOAT3 cameraPos;

	//縦揺れ時間
	float yMoveTime;

	//ゆっくり上下
	float sinwave;

	const float STAGE_ROTATE_SPEED = 3.0f;
	const float WAVE_VELOCITY = 5.0f;
	const float SCALE_UP_SPEED = 0.03f;
	const float SCALE_DOWN_SPEED = 0.05f;
	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };
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

	//trueで拡大、それ以外で縮小する関数
	void StageScaling(Transform* stage_, bool big , float rate);

};

