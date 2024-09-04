#pragma once
#include "Engine/GameObject.h"

class Enemy;

class JewelBullet :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;

    XMFLOAT3 bulletPos_;

    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;

    int deleteTime_;
    int killCount_;
    int score_;

    /*スコア換算の定数たち*/
    const int SCORE_BRACKETS[6] = { 25, 50, 75, 150, 300, 1500 };
    const int SCORE_BRACKET_THRESHOLD1 = 5;
    const int SCORE_BRACKET_THRESHOLD2 = 10;
    const int SCORE_BRACKET_COUNT = 6;
public:
    //コンストラクタ
    JewelBullet(GameObject* parent);

    //デストラクタ
    ~JewelBullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    // 弾の方向をプレイヤーの前方ベクトルからもらう
    void BulletDirection(XMVECTOR _dir);

    // 弾の位置をプレイヤーの位置から算出する
    void BulletPosition(XMFLOAT3 _pos);
    void BulletPosition(float x, float y, float z);

    // 弾丸のY軸回転角度を得る
    void BulletRotate(XMFLOAT3 _rote) {transform_.rotate_.y = _rote.y + 180;};

    // 弾を打つ処理
    void Shoot();

    // 何かに当たったら
    void OnCollision(GameObject* pTarget)override;

    // 敵のキル数からスコアを計算します
    int CalculateScore(int killCount);

    void SetKillCount(int count);

    int SetStageHandle();
};
