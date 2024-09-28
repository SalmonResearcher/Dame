#pragma once
#include "Engine/GameObject.h"

class Player;

//納品箱を管理するクラス
class JewelBox : public GameObject
{
    int hModel_;    //モデル番号

    int jewel_;
    int score_;

    const XMFLOAT3 COLLIDER_POSITION = { 0,1,0 };
    const float COLLIDER_RADIUS = 1.5f;

public:
    //コンストラクタ
    JewelBox(GameObject* parent);

    //デストラクタ
    ~JewelBox();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデル番号を返す
    int GetModelHandle() { return hModel_; };

    void OnCollision(GameObject* pTarget);

    void AddScore(int _score) { score_ += _score; };

    int ReturnJewel() { return jewel_; };
    int GetKillScore() { return score_; };
    int SetStageHandle();
};