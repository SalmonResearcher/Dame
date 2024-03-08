#pragma once
#include "Engine/GameObject.h"
class Cammera : public GameObject
{
    int hModel_;    //モデル番号
    XMFLOAT3 move_ = { 0,0,0 };
    int time;

public:
    //コンストラクタ
    Cammera(GameObject* parent);

    //デストラクタ
    ~Cammera();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetPlayerVector(XMVECTOR _vecPlayer);
    void GetPlayerPosition(XMFLOAT3 _playerPos);
};