#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class TutorialStage : public GameObject
{
    int hModel_;    //モデル番号
    int hModel2_;

    Transform transSky_;


    float signY_;
    float jewelY_;
    bool spawned_ = false;

    // 定数の定義
    const XMFLOAT3 INIT_POSITION = { 500, -6, 0 };

    const float SIGN_POSITION_Z[4] = { 7.0f, 25.0f, 35.0f, 45.0f };
    const float JEWEL_POSITION_Z = 20.0f;
    const float PLAYER_POSITION_Y_THRESHOLD = -15.0f;
    const float PLAYER_POSITION_Z_THRESHOLD = 65.0f;

    //UI情報
    const int JEWEL_POSITION_X = 1150;
    const int JEWEL_POSITION_Y = 110;
    const int SCORE_POSITION_X = 950;
    const int SCORE_POSITION_Y = 45;
    const int TIMER_POSITION_X = 600;
    const int TIMER_POSITION_Y = 45;

    // スコアとタイマーの初期値
    const int INITIAL_SCORE = 0;
    const int INITIAL_TIMER_LIMIT = 0;

    // ジュエルボックスの位置
    const XMFLOAT3 JEWEL_BOX_POSITION = { 0, -7, 55 };

    //看板の反転
    const XMFLOAT3 DEFAULT_SIGN_ROTATION = { 0, 180, 0 };

public:
    //コンストラクタ
    TutorialStage(GameObject* parent);

    //デストラクタ
    ~TutorialStage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデル番号を返す
    int GetModelHandle() { return hModel_; }
};