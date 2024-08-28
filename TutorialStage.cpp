#include "TutorialStage.h"
#include "TutorialBoard.h"
#include "Engine/Model.h"

#include "Player.h"
#include "CharacterDisplay.h"
#include "JewelBox.h"
#include "Jewel.h"
#include "Signboard.h"

namespace
{
    JewelBox* pJewelBox_;
    Jewel* pJewel_;
    SignBoard* pSign1_;
    SignBoard* pSign2_;
    SignBoard* pSign3_;
    SignBoard* pSign4_;
    TutorialBoard* pBoard_;
    Player* pPlayer_;
    CharacterDisplay* pDisplay_;

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

    pJewelBox_ = Instantiate<JewelBox>(this);

    pJewel_ = Instantiate<Jewel>(this);

    pSign1_ = Instantiate<SignBoard>(this);
    pSign2_ = Instantiate<SignBoard>(this);
    pSign3_ = Instantiate<SignBoard>(this);
    pSign4_ = Instantiate<SignBoard>(this);
    pBoard_ = Instantiate<TutorialBoard>(this);

    pDisplay_ = Instantiate<CharacterDisplay>(this);

    pDisplay_->CreateJewels(1);
    pDisplay_->CreateScores(1);
    pDisplay_->CreateTimers(1);

    pDisplay_->SetJewelPosition(0, 45, 650);
    pDisplay_->SetScorePosition(0, 950, 45);
    pDisplay_->SetTimerPosition(0, 850, 45);

    pDisplay_->ScoreCountStart(0);

    pDisplay_->SetTimerLimit(0, 00);

    pJewelBox_->SetPosition(0, -7, 55);

    signY_ = pSign1_->GetPosition().y;
    jewelY_ = pJewel_->GetPosition().y;
    pSign1_->SetRotate(0, 180, 0);
    pSign2_->SetRotate(0, 180, 0);
    pSign3_->SetRotate(0, 180, 0);
    pSign4_->SetRotate(0, 180, 0);

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
    pSign2_->SetPosition(0, signY_, 25);
    pSign3_->SetPosition(0, signY_, 35);
    pSign4_->SetPosition(0, signY_, 45);

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