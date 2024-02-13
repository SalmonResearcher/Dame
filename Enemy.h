#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;
    Transform transEnemy_;
    XMFLOAT3 target_;
    float moveY = 0.0f;

    bool isJumping;

public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    
};