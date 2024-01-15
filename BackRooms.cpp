#include "BackRooms.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

#include "Player.h"

BackRooms::BackRooms(GameObject* parent)
 :GameObject(parent, "BackRooms"), hModel_(-1)
{
}

//デストラクタ
BackRooms::~BackRooms()
{
}

//初期化
void BackRooms::Initialize()
{
    hModel_ = Model::Load("BackRooms.fbx");
    assert(hModel_ >= 0);
}

//更新
void BackRooms::Update()
{
}

//描画
void BackRooms::Draw()
{
    Model::SetTransform(hModel_, transBackRooms_);
    Model::Draw(hModel_);
}

//開放
void BackRooms::Release()
{
}