#pragma once
#include "Engine/GameObject.h"




class StageSelectScene :
    public GameObject
{
private:




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

