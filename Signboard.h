#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

class SignBoard :
    public GameObject
{
    enum STATEVFX {
        HIT,
        JEWEL
    };

    int hModel_;    //モデル番号
    int hStage_;
    int animTime_;
    bool isAnimEnd_;    //animationが終わったか
    int hSound_;

    int hEmit_;//VFXの番号
    bool stopEmit_;
    EmitterData vfx_;

    //アニメーション定数
    const int START_ANIM = 0;
    const int END_ANIM = 60;
    const float ANIM_SPEED = 1.0f;

    //コライダー
    XMFLOAT3 colliderPosition = { 0.0f,1.0f,0.0f };
    const float COLLIDER_SCARE = 1.25f;

        /*VFXの定数達*/
    // 位置オフセットの定数
    static constexpr float HIT_EFFECT_OFFSET_Y = 0.7f;
    // エフェクトのサイズ
    static constexpr XMFLOAT2 EFFECT_SIZE_LARGE = XMFLOAT2(4, 4);
    // エフェクトのスケール
    static constexpr XMFLOAT2 EFFECT_SCALE_DEFAULT = XMFLOAT2(1.2, 1.2);
    // ライフタイム
    static constexpr int LIFETIME_SHORT = 5;
    // 回転量
    static constexpr XMFLOAT3 EFFECT_SPIN = XMFLOAT3(0, 0, 15.0f);



public:
    //コンストラクタ
    SignBoard(GameObject* parent);

    //デストラクタ
    ~SignBoard();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //レイキャスト用ステージ
    int SetStageHandle();

    //何かに当たった
    void OnCollision(GameObject* pTarget) override;

    void CreateVFX(STATEVFX svfx);

    void DestroyVFX();
};
