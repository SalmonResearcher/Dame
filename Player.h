#pragma once
#include "Engine/GameObject.h"


class Player :
    public GameObject
{
private:
    Transform tPlayer_; //プレイヤーのトランスフォーム
    Transform tCamera;  //カメラのトランスフォーム

    XMVECTOR vecPlayer_;    //プレイヤーの向いている方向ベクトル
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;


    int hModel_;
    const float SPEED = 0.15;  //カメラの回転速度,プレイヤーの移動速度
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;



    XMFLOAT3 GetPlayerPos()
    {
        return tPlayer_.position_;
    }
};

