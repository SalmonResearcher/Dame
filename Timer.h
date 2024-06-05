#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"



class Timer :public GameObject
{
private:
	Text* num;

	int frame;
	bool active;
	int drawX;
	int drawY;


public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Timer(GameObject* parent);

	~Timer();


	//初期化
	void Initialize() override; 

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetLimit(float seconds);

	void Start();

	void Stop();

	bool IsFinished();

};