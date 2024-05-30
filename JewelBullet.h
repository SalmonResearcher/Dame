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
    int time_;
    bool isJumping_;


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

    void Shoot();

    //Jewel Shoot Direction / XMVECTOR Start, XMVECTOR End
    void BulletDirection(XMVECTOR _dir) { playerForwardVec_ = _dir; };
    void BulletPosition(XMFLOAT3 _pos) { playerPos_ = _pos; };
    void BulletRotate(XMFLOAT3 _rote) { tJBullet_.rotate_.y = _rote.y + 180; ; };
};
