#pragma once
#include "Engine/GameObject.h"
class EnemySpawn : public GameObject
{
    int interval_;  //〇F経過したらスポーン
    int time_;      //1Fごとにカウント
    bool canSpawn_;

    int minX_, maxX_;

public:
    //コンストラクタ
    EnemySpawn(GameObject* parent);

    //デストラクタ
    ~EnemySpawn();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //スポーンポイントを設定
    void SetSpawnPoint(XMFLOAT3 point) { transform_.position_ = point; }
    XMFLOAT3 GetSpawnPoint() { return transform_.position_; };

    //スポーンからスポーンまでの合間時間（1F単位）
    void SetInterval(int _interval) { interval_ = _interval; };

    void StartSpawn() { canSpawn_ = true; };
    void StopSpawn() { canSpawn_ = false; };

    void SetRandomX(float _min, float _max) { minX_ = _min; maxX_ = _max; };

    float getRandomFloat(float min, float max);
};