#include "TutorialStage.h"
#include "Engine/Model.h"

#include "JewelBox.h"

namespace
{
    JewelBox* pJewelBox1_;
    JewelBox* pJewelBox2_;
}

//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent)
    :GameObject(parent, "TutorialStage"), hModel_(-1), hModel2_(-1)
{
}

//デストラクタ
TutorialStage::~TutorialStage()
{
}

//初期化
void TutorialStage::Initialize()
{
    hModel_ = Model::Load("TutorialStage.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("SkySphere.fbx");
    assert(hModel2_ >= 0);

    pJewelBox1_ = Instantiate<JewelBox>(this);
    pJewelBox2_ = Instantiate<JewelBox>(this);

    pJewelBox1_->SetPosition(0, 0, 12);
    pJewelBox2_->SetPosition(-12, 0, 18);

}

//更新
void TutorialStage::Update()
{
    transSky_.rotate_.y += 0.02f;
    transSky_.scale_ = { 0.8,0.8,0.8 };
}

//描画
void TutorialStage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
    Model::SetTransform(hModel2_, transSky_);
    Model::Draw(hModel2_);
}

//開放
void TutorialStage::Release()
{
}