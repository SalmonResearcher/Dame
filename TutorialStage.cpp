#include "TutorialStage.h"
#include "TutorialBoard.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"

#include "Player.h"
#include "CharacterDisplay.h"
#include "JewelBox.h"
#include "Jewel.h"
#include "Signboard.h"
#include "JewelBullet.h"
#include "SkySphere.h"

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
    JewelBullet* pBullet_;
    SkySphere* pSky_;

    // 定数の定義
    const XMFLOAT3 INIT_POSITION = { 500, -6, 0 };

    const float SIGN_POSITION_Z[] = { 7.0f, 25.0f, 35.0f, 45.0f };
    const float JEWEL_POSITION_Z = 20.0f;
    const float PLAYER_POSITION_Y_THRESHOLD = -15.0f;
    const float PLAYER_POSITION_Z_THRESHOLD = 65.0f;


    // スコアとタイマーの初期値
    const int INITIAL_SCORE = 0;
    const int INITIAL_TIMER_LIMIT = 0;

    // ジュエルボックスの位置
    const XMFLOAT3 JEWEL_BOX_POSITION = { 0, -7, 55 };

    //看板の反転
    const XMFLOAT3 DEFAULT_SIGN_ROTATION = { 0, 180, 0 };

}

// コンストラクタ
TutorialStage::TutorialStage(GameObject* parent)
    : GameObject(parent, "TutorialStage"), hModel_(-1)
{
}

// デストラクタ
TutorialStage::~TutorialStage()
{
}

// 初期化
void TutorialStage::Initialize()
{
    hModel_ = Model::Load("TutorialStage.fbx");
    assert(hModel_ >= 0);

    pSky_ = Instantiate<SkySphere>(this);

    pJewelBox_ = Instantiate<JewelBox>(this);
    pBullet_ = Instantiate<JewelBullet>(this);
    pBullet_->BulletPosition(INIT_POSITION);

    pJewel_ = Instantiate<Jewel>(this);
    pJewel_->SetPosition(INIT_POSITION);
    pJewel_->KillMe();

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

    pDisplay_->ScoreCountStart(INITIAL_SCORE);
    pDisplay_->SetTimerLimit(INITIAL_TIMER_LIMIT, INITIAL_TIMER_LIMIT);    
    pJewelBox_->SetPosition(JEWEL_BOX_POSITION);

    signY_ = pSign1_->GetPosition().y;
    jewelY_ = pJewel_->GetPosition().y;

    // サインボードの回転を設定
    pSign1_->SetRotate(DEFAULT_SIGN_ROTATION);
    pSign2_->SetRotate(DEFAULT_SIGN_ROTATION);
    pSign3_->SetRotate(DEFAULT_SIGN_ROTATION);
    pSign4_->SetRotate(DEFAULT_SIGN_ROTATION);

    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

// 更新
void TutorialStage::Update()
{
    // ジュエルのスポーン管理
    if (pPlayer_->GetJewelCount() <= 0 && !spawned_)
    {
        pJewel_ = Instantiate<Jewel>(this);
        pJewel_->SetPosition(0, jewelY_, JEWEL_POSITION_Z);
        spawned_ = true;
    }
    if (pPlayer_->GetJewelCount() >= 1)
    {
        spawned_ = false;
    }

    // サインボードの位置を設定
    pSign1_->SetPosition(0, signY_, SIGN_POSITION_Z[0]);
    pSign2_->SetPosition(0, signY_, SIGN_POSITION_Z[1]);
    pSign3_->SetPosition(0, signY_, SIGN_POSITION_Z[2]);
    pSign4_->SetPosition(0, signY_, SIGN_POSITION_Z[3]);


    // プレイヤーの位置に応じたシーンの変更
    if (pPlayer_->GetPlayerPosition().z >= PLAYER_POSITION_Z_THRESHOLD || pPlayer_->GetPlayerPosition().y <= PLAYER_POSITION_Y_THRESHOLD)
    {
        SceneManager* pSceneManager = static_cast<SceneManager*>(FindObject("SceneManager"));
        pSceneManager->ChangeScene(SCENE_ID_SELECT);
    }
}

//描画
void TutorialStage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TutorialStage::Release()
{
}