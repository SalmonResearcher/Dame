#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

#include "Player.h"
#include "Engine/VFX.h"


class SphereCollider;
class StateManager;

enum STATEVFX {
    HIT,
    JEWEL,
    DEATH
};

class Enemy : public GameObject
{
    SphereCollider* pSpher_;
    Player* pPlayer_;
    StateManager* pStateManager_;

    int hModel_;    //モデル番号
    int hDeathSound_;    //サウンド番号
    int hHitSound_; //ヒットした時の音

    int hStage_;    //ステージモデル
    int hPlayer_;   //プレイヤーのモデル番号

    int hEmit_;     //エフェクト番号
    bool stopEmit_; //エフェクトを止める

    int killedByJewel_;

    XMVECTOR vPosition_;    //自身の位置ベクトル
    XMFLOAT3 target_;       //プレイヤーの位置
    XMVECTOR vTarget_;      //プレイヤーの位置ベクトル
    XMVECTOR direction_;    //プレイヤーと敵の方向ベクトル
    float toPlayerdir_;      //プレイヤーまでの直線距離

    int waitTime_ = 0;

    //死んでいるかどうか
    bool isDead_ = false;

    //倒されたカウントされたかどうか
    bool counted_;           

    float volume_;

    EmitterData vfx_;

    //プレイヤーが近くにいるか
    bool isNearPlayer_;

    //攻撃が終わったか
    bool isAttackEnd_; 
    
    /*VFXの定数達*/
    // 位置オフセットの定数
    static constexpr float HIT_EFFECT_OFFSET_Y = 0.7f;
    // エフェクトのサイズ
    static constexpr XMFLOAT2 EFFECT_SIZE_LARGE = XMFLOAT2(4, 4);
    static constexpr XMFLOAT2 EFFECT_SIZE_SMALL = XMFLOAT2(1, 1);
    // エフェクトのスケール
    static constexpr XMFLOAT2 EFFECT_SCALE_DEFAULT = XMFLOAT2(1.2, 1.2);
    static constexpr XMFLOAT2 EFFECT_SCALE_SMALL = XMFLOAT2(0.99, 0.99);
    // ライフタイム
    static constexpr int LIFETIME_SHORT = 5;
    static constexpr int LIFETIME_LONG = 25;
    // その他の定数
    static constexpr float EFFECT_SPEED_DEATH = 0.4f;
    static constexpr float EFFECT_GRAVITY = 0.02f;
    static constexpr XMFLOAT3 EFFECT_SPIN = XMFLOAT3(0, 0, 15.0f);
    static constexpr XMFLOAT3 POSITION_RND_DEATH = XMFLOAT3(0.8f, 0, 0.8f);
    static constexpr XMFLOAT3 DIRECTION_RND_DEATH = XMFLOAT3(15, 15, 15);
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

    //距離に応じて音量を変える
    float SoundDistance(float distance,float falloff);

    //Floatのランダムな値を生成します
    float GenerateRandomFloat(float min, float max);

    //エフェクト
    void CreateVFX(STATEVFX svfx);

    //エフェクトの消去
    void DestroyVFX();

    bool GetEnemyDeath() { return isDead_; };
    bool IsNearPlayer() { return  isNearPlayer_; };
    bool IsAttackEnd() { return isAttackEnd_; };
    void SetAttackTime();
    void SetDeadTime();
};