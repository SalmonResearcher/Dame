#pragma once
#include "Engine/GameObject.h"

class Player;

//空球を管理するクラス
class SkySphere : public GameObject
{
    Player* pPlayer_;

    int hModel_;    //モデル番号

    const float ROTATE_SPEED = 0.01f;
    const XMFLOAT3 SCALE = { 0.75f,0.75f,0.75f };
public:
    //コンストラクタ
    SkySphere(GameObject* parent);

    //デストラクタ
    ~SkySphere();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデル番号を返す
    int GetModelHandle() { return hModel_; }
};