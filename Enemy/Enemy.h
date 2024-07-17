#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SphereCollider.h"

#include "../Player.h"

class SphereCollider;

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
    SphereCollider* pSpher;
    Player* pPlayer;

    int hModel_;    //モデル番号
    int hSound_;    //サウンド番号
    int hSoundHit_; //ヒット

    int hStage_;    //ステージモデル
    int hPlayer_;   //プレイヤーのモデル番号

    int killed_by_Jewel;

    STATE states;
    int curState;   //1f前の状態
    bool isChange;  //ステートを変更するかどうか（アニメーションの設定の際に使用）

    XMVECTOR vPosition_;    //自身の位置ベクトル
    XMFLOAT3 target_;       //プレイヤーの位置
    XMVECTOR vTarget_;      //プレイヤーの位置ベクトル
    XMVECTOR direction_;    //プレイヤーと敵の方向ベクトル
    float toPlayerdir;      //プレイヤーまでの直線距離

    int waitTime_ = 0;
    int killcount;

    bool isDead = false;
    bool counted;

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

    void Attack();

    void Death();
    void JewelDeath();

    void ChangeAnime(STATE state);

    
};