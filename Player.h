#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "PlayerStateManager.h"

class Stage;

class Player :
    public GameObject
{
private:
    Transform tPlayer_; //プレイヤーのトランスフォーム
    Transform tCamera;  //カメラのトランスフォーム

    XMVECTOR vecPlayer_;    //プレイヤーの進んでいる方向ベクトル
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;

    
    int hModel_;
    int hStage_;
    int hEnemy_;

    const float MAXSPEED = 0.15;  //カメラの回転速度,プレイヤーの移動速度
    float speed_ = 0;
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

protected:
    PlayerStateManager* pState_;

    Stage* pStage_;    //モデル番号を取得



public:
    //プレイヤーの大きさ。
    // 基本的には中央が原点なので2で割る。
    const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void StageRay();
    void GetState() {};

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
        return 0;
    }


};

