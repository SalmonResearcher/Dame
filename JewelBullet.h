#pragma once
#include "Engine/GameObject.h"

class Enemy;

class JewelBullet :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;

    XMFLOAT3 bulletPos_;

    int deleteTime_;
    int killCount_;
    int score_;
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

    /// <summary>
    /// 弾の方向をプレイヤーの前方ベクトルからもらう
    /// </summary>
    /// <param name="_dir">XMVECTOR：方向ベクトル</param>
    void BulletDirection(XMVECTOR _dir);

    /// <summary>
    /// 弾の位置をプレイヤーの位置から算出する
    /// </summary>
    void BulletPosition(XMFLOAT3 _pos);

    /// <summary>
    /// 弾丸のY軸回転角度を得る
    /// </summary>
    /// <param name="_rote"></param>
    void BulletRotate(XMFLOAT3 _rote) {transform_.rotate_.y = _rote.y + 180;};
    /// <summary>
    /// 弾を打つ処理
    /// </summary>
    void Shoot();

    /// <summary>
    /// 何かに当たったら
    /// </summary>
    void OnCollision(GameObject* pTarget)override;

    /// <summary>
    /// 敵のキル数からスコアを計算します
    /// </summary>
    int CalculateScore(int killCount);


    void SetKillCount(int count);
};
