#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

class Jewel :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;
    int time_;
    float rotY = 0.0f;
    bool jewelRotate_;

    int hEmit_;//VFXの番号
    bool stopEmit_;
    EmitterData vfx;

    /*VFXの定数たち*/
    const XMFLOAT3 PARTICLE_POSITION_RND = XMFLOAT3(0.8f, 0.0f, 0.8f);
    const XMFLOAT3 PARTICLE_DIRECTION = XMFLOAT3(0.0f, 1.0f, 0.0f);
    const XMFLOAT3 PARTICLE_DIRECTION_RND = XMFLOAT3(10.0f, 10.0f, 10.0f);
    const XMFLOAT2 PARTICLE_SIZE = XMFLOAT2(1.5f, 1.5f);
    const XMFLOAT2 PARTICLE_SCALE = XMFLOAT2(0.99f, 0.99f);
    const int PARTICLE_LIFETIME = 110;
    const float PARTICLE_SPEED = 0.05f;
    const XMFLOAT3 PARTICLE_SPIN = XMFLOAT3(0.0f, 0.0f, 0.1f);
    const float PARTICLE_GRAVITY = 0.0f;
    const float PARTICLE_DELAY = 0.0f;

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

    // イージング関数
    float easeInOutCubic(float x) 
    {
        if (x < 0.5) {
            return 4.0f * pow(x, 3);
        }
        else {
            return 1.0f - pow(-2 * x + 2, 3) / 2.0f;
        }
    }

    //例キャスト用ステージ
    int SetStageHandle();

    //何かに当たった
    void OnCollision(GameObject* pTarget) override;

    void CreateVFX();

    void DestroyVFX();
};
