#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"

class Stage;

class Player :
    public GameObject
{
private:
    Transform tPlayer_; //プレイヤーのトランスフォーム
    Transform tCamera;  //カメラのトランスフォーム

    XMVECTOR vecPlayer_;    //プレイヤーの向いている方向ベクトル
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;

    const XMFLOAT3 PLAYERSIZE{ 1,1,1 };
    int hModel_;
    const float MAXSPEED = 0.15;  //カメラの回転速度,プレイヤーの移動速度
    float speed_ = 0;
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

    Stage* pStage;    //モデル番号を取得
    int hStage_;//ステージモデルの番号

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void StageRay();


    XMFLOAT3 GetPlayerPos()
    {
        return tPlayer_.position_;
    }

    XMVECTOR GetPlayerVec()
    {
        return vecPlayer_;
    }

    //プレイヤーが判定するステージ
    int GetPlayerStage()
    {
        return 
    }
};

