#include "TutorialStage.h"
#include "TutorialBoard.h"
#include "Engine/Model.h"

#include "Player.h"

#include "JewelBox.h"
#include "Jewel.h"
#include "Signboard.h"

namespace
{
    JewelBox* pJewelBox1_;
    JewelBox* pJewelBox2_;
    Jewel* pJewel_;
    SignBoard* pSign1_;
    TutorialBoard* pBoard_;
    Player* pPlayer_;

    float signY_;
    float jewelY_;
    bool spawned_ = false;
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

    pJewel_ = Instantiate<Jewel>(this);

    pSign1_ = Instantiate<SignBoard>(this);
    pBoard_ = Instantiate<TutorialBoard>(this);

    pJewelBox1_->SetPosition(0, 0, 12);
    pJewelBox2_->SetPosition(-12, 0, 18);

    signY_ = pSign1_->GetPosition().y;
    jewelY_ = pJewel_->GetPosition().y;
    pSign1_->SetRotate(0, 180, 0);

    pPlayer_ = static_cast<Player*>(FindObject("Player"));

}

//更新
void TutorialStage::Update()
{
    if (pPlayer_->GetJewelCount() <= 0 && !spawned_)
    {
        pJewel_ = Instantiate<Jewel>(this);
        pJewel_->SetPosition(0, jewelY_, 20);
        spawned_ = true;
    }
    if (pPlayer_->GetJewelCount() >= 1)
    {
        spawned_ = false;
    }

    pSign1_->SetPosition(0, signY_, 7);
    pJewelBox1_->SetPosition(0, 0, 20);

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