#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SphereCollider.h"

#include "../Player.h"

enum STATE {
    MOVE,
    ATTACK,
    DEATH,
    MAX
};

struct {
    int startFrame;
    int endFrame;
    float animeSpeed;

};


class Enemy : public GameObject
{
    int hModel_;    //モデル番号

    int hStage_;
    int hPlayer_;

    STATE states;
    int curState;   //1f前の状態
    bool isChange;  //ステートを変更するかどうか（アニメーションの設定の際に使用）

    Transform tEnemy_;

    XMVECTOR vPosition_;    //自身の位置ベクトル
    XMFLOAT3 target_;       //プレイヤーの位置
    XMVECTOR vTarget_;      //プレイヤーの位置ベクトル
    XMVECTOR direction_;    //プレイヤーと敵の方向ベクトル
    float toPlayerdir;      //プレイヤーまでの直線距離

    XMFLOAT3 bonepos;
    float moveY = 0.0f;
    float speed = 0.5f;

    int startFrame;
    int endFrame;
    float animeSpeed;
    int waitTime = 0;

    bool isDead = false;

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

    void ChangeAnime(STATE state);

};