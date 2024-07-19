#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class TutorialStage : public GameObject
{
    int hModel_;    //モデル番号
    int hModel2_;
    Transform transSky_;


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