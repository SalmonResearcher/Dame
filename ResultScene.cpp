#include "ResultScene.h"

#include "CharacterDisplay.h"

#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Global.h"
//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "Title"), hImage_(0)
{
}

//初期化
void ResultScene::Initialize()
{
	pDisplay_ = Instantiate<CharacterDisplay>(this);

	score_ = Global::GetScore();

	pDisplay_->SetScorePosition(850, 5);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
	pDisplay_->DrawScore(score_);
}

//開放
void ResultScene::Release()
{
}