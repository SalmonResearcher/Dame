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
    int time_;
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

    //イージング関数
    float easeInOutCubic(float x) {
        return x < 0.5 ? 4 * pow(x, 3) : 1 - pow(-2 * x + 2, 3) / 2;
    }

    void Shoot();

};
