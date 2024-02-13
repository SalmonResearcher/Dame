#pragma once
#include "Engine/GameObject.h"
class Jewel :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;

    Transform trJewel_;

    float rotY = 0.0f;
    float grabity_ = 0.0f;
    int time;
    bool jewelRotate_;

public:
    //コンストラクタ
    Jewel(GameObject* parent);

    //デストラクタ
    ~Jewel();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};
