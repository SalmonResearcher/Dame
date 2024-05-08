#pragma once
#include "../../Engine/GameObject.h"
#include "../../Player.h"

class Fafro : public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;
    Transform transFafro_;
    XMFLOAT3 target_;
    float moveY = 0.0f;

    bool isJumping;
    bool dead = false;
    int startFrame;
    int endFrame;
    float animeSpeed;

    int gloTime;

public:
    //コンストラクタ
    Fafro(GameObject* parent);

    //デストラクタ
    ~Fafro();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    int GetModelHandle() { return hModel_; }

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    void ChasePlayer(XMFLOAT3& target_, float speed);

};