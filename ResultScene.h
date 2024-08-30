#pragma once
#include "Engine/GameObject.h"
#include <string.h>

class CharacterDisplay;

class ResultScene :public GameObject
{
private:
	Transform trPict_;
	int hImage_;
	int hCountSound_;
	int hMoneySound_;

	int hBGM_;

	float pitch_;

	CharacterDisplay* pDisp_;

	int killCount_;
	int jewel_;
	int jewelKill_;

	int totalScore_;
	int showScoreTime = 0;

	int soundtimer;

	bool countStart[4];

	bool countEnd = false;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SoundPlay(int handle,int interval);

	void SoundStop(int handle);

};

