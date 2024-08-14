#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

#include "Player.h"
#include "Engine/VFX.h"

class SphereCollider;

enum STATE {
    MOVE,
    ATTACK,
    DEATH,
    MAX
};

class Enemy : public GameObject
{
    SphereCollider* pSpher;
    Player* pPlayer;

    int hModel_;    //モデル番号
    int hDeathSound_;    //サウンド番号
    int hHitSound_; //ヒット

    int hStage_;    //ステージモデル
    int hPlayer_;   //プレイヤーのモデル番号

    int hEmit_; //エフェクト番号
    bool stopEmit_;

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

    bool isDead = false;    //死んでいるかどうか
    bool counted;           //倒されたカウントされたかどうか

    float volume;

    EmitterData vfx;

    bool isNearPlayer_;//プレイヤーが近くにいるか
    bool isAttackEnd_; //攻撃が終わったか

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

    //State
    void Walk();
    void Attack();
    void AttackCollision();
    void Dead();



    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    int GetModelHandle() { return hModel_; }

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    void ChasePlayer(XMFLOAT3& target_, float speed);

    void JewelDeath();//宝石によってやられた

    void ChangeAnime(STATE state);

    //距離に応じて音量を変える
    float SoundDistance(float distance,float falloff);

    //Floatのランダムな値を生成します
    float GenerateRandomFloat(float min, float max);

    //エフェクト
    void CreateVFX(int num);

    //エフェクトの消去
    void DestroyVFX();

    bool GetEnemyDeath() { return isDead; };
    bool IsNearPlayer() { return  isNearPlayer_; };
    bool IsAttackEnd() { return isAttackEnd_; };

};