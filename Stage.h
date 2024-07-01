#pragma once
#include "Engine/GameObject.h"

class Sprite;
class Player;
class Stage;
class Jewel;

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    Player* pPlayer_;
    Stage* pStage_;
    Jewel* pJewel_;


    int hModel_;    //モデル番号
    int hModel2_;
    Transform transStage_;
    Transform transSky_;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

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