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

	enum
	{
		IMAGE_1,
		IMAGE_2,
		MAX_IMAGE
	};
	XMFLOAT3 cameraPos;


	int hSkysphere;
	Transform trSky;

	int hBGM_;
	int hImage_[MAX_IMAGE];
	int hStage_[MAX_STAGE];

	int alImage_[MAX_IMAGE];	//alpha値

	Transform trStage[MAX_STAGE];	//ステージプレビューのトランスフォーム
	Transform trImage_[MAX_IMAGE];

	//ミニステージの移動
	float moveX;
	//左右の＜＞の動き
	float moveXImage;

	//ステージの移動量
	const float STAGE_MOVE = 0.25f;

	//回転用の時間
	float timer_;

	//縦に揺れる速さ
	const float Y_MOVE_SPEED = 0.06f;

	//ステージ選択するときのカウント
	int selectCount_;

	//そのステージで止まったかどうか
	bool isStageStop = false;

	//縦揺れ時間
	float yMoveTime;

	//ゆっくり上下させる変数
	float sinwave;

	const float STAGE_ROTATE_SPEED = 3.0f;
	const float WAVE_VELOCITY = 5.0f;
	const float SCALE_UP_SPEED = 0.03f;
	const float SCALE_DOWN_SPEED = 0.05f;
	const XMFLOAT3 STAGE_SCALE = { 0.2f,0.2f,0.2f };
	const XMFLOAT3 STAGE_BIG = { 0.4f,0.4f,0.4f };

	//最大
	const XMFLOAT3 IMAGE_SCALE = { 0.3,0.3,0.3 };
	const int IMAGE_MAX_ALPHA = 192;		//画像の最大不透明度
	const int IMAGE_ROTATE = 180;			//画像の回転
	const float IMAGE_POSITiON = 0.8f;		//画像の位置
	const int IMAGE_WAVE_VEL = 100;			//画像の横揺れのつよさ

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

