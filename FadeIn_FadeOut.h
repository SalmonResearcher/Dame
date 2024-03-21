#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class FadeIn_FadeOut : public GameObject
{
private:
	short timer;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	FadeIn_FadeOut(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//フェードインを設定
	//引数：int　完了までのフレーム（デフォルトは30F）
	void FadeIn_B(int _frame);
	//フェードインを設定
	//引数：int 完了までのフレーム（デフォルトは30F）
	void FadeIn_B();

	void FadeIn_W();
	void FadeIn_W(int _frame);


	void FadeOut_B();
	void FadeOut_W();

};