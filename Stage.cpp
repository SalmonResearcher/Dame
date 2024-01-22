#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

#include "Player.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    hModel_ = Model::Load("Stage3.fbx");
    assert(hModel_ >= 0);
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transStage_);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}