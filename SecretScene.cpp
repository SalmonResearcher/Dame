#include "SecretScene.h"
#include "Engine/Model.h"
#include "Player.h"

//コンストラクタ
SecretScene::SecretScene(GameObject* parent)
	: GameObject(parent, "SecretScene") , hModel_(-1)
{
}

//初期化
void SecretScene::Initialize()
{
	hModel_ = Model::Load("LevelEntrance.fbx");
	assert(hModel_ >= 0);

	Instantiate<Player>(this);
}

//更新
void SecretScene::Update()
{
}

//描画
void SecretScene::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

//開放
void SecretScene::Release()
{
}
