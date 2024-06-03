#pragma once
#include "Engine/GameObject.h"
class JewelBullet :
    public GameObject
{
    int hModel_;    //モデル番号
    int hStage_;

    Transform tJBullet_;
    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;

    XMVECTOR bulletInitPos;
    XMFLOAT3 initPos;

    int deleteTime_;


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
    void BulletDirection(XMVECTOR _dir) { playerForwardVec_ = _dir; };

    /// <summary>
    /// 弾の位置をプレイヤーの位置から算出する
    /// </summary>
    void BulletPosition(XMFLOAT3 _pos) {
        playerPos_ = _pos;
        // 弾丸の初期位置 = プレイヤー位置 + (前方ベクトル * 距離オフセット)
        XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
        XMStoreFloat3(&initPos, bulletInitPos);
    };

    /// <summary>
    /// 弾の回転を受け取る
    /// </summary>
    void BulletRotate(XMFLOAT3 _rote) { tJBullet_.rotate_.y = _rote.y + 180; };

    /// <summary>
    /// 弾を打つ処理
    /// </summary>
    void Shoot();

    /// <summary>
    /// 何かに当たったら
    /// </summary>
    void OnCollision(GameObject* pTarget)override;

};
