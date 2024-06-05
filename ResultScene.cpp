#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//初期化
void ResultScene::Initialize()
{
	pDisp_ = Instantiate<CharacterDisplay>(this);
	pDisp_->ScorePosition(40, 40, score);

	pDisp_->TimerPosition(0, 0, false);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	
}

//開放
void ResultScene::Release()
{
}