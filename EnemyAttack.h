#pragma once
#include "Engine/GameObject.h"
class EnemyAttack : public GameObject
{
    int hModel_;    //モデル番号
    XMFLOAT3 pos_;
    int time_;

public:
    //コンストラクタ
    EnemyAttack(GameObject* parent);

    //デストラクタ
    ~EnemyAttack();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetAttackPosition(XMFLOAT3 _pos) { pos_ = _pos; }

    void SetTime(int _time) { time_ = _time; };

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

};