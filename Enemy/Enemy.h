#pragma once
#include "../Engine/GameObject.h"
#include "../Player.h"

enum STATE{
    MOVE,
    ATTACK,
    DEATH,
    MAX
};


class Enemy : public GameObject
{
    int hModel_;    //モデル番号

    int hStage_;
    int hPlayer_;

    STATE states;

    Transform transEnemy_;

    XMVECTOR vPosition_; //自身のいち
    XMFLOAT3 target_;
    XMVECTOR vTarget_;
    XMVECTOR direction_;

    float moveY = 0.0f;
    float speed = 0.5f;

    int startFrame;
    int endFrame;
    float animeSpeed;
 
    bool isLive = true;

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

    int GetModelHandle() { return hModel_; }

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    void ChasePlayer(XMFLOAT3& target_, float speed);

    void AttackPlayer();
    
    void Death();

    void 
};