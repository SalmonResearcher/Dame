#pragma once
#include "Engine/GameObject.h"
class JewelBullet :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;

    Transform trJBullet_;
    XMVECTOR jewelDir_;
    int time_;
    bool isJumping_;


public:
    //コンストラクタ
    JewelBullet(GameObject* parent);

    //デストラクタ
    ~JewelBullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Shoot();

    //Jewel Shoot Direction / XMVECTOR Start, XMVECTOR End
    void SetDirection(XMVECTOR _dirStart) { jewelDir_ = _dirStart; };
};
