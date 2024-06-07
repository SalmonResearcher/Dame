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
    XMFLOAT3 smoothCam;
    
    int hModel_;
    int hStage_;
    int hEnemy_;

    float mouseSens = 1;

    float attackStart;
    float attackEnd;
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //カメラの回転速度,プレイヤーの移動速度
    float speed_ = 0;
    float jewelCount_;
    float weight_;
    short moveSpeed;
    short dash_;
    float moveY = 0;
    bool isJumping = false;
    bool isHit;

    int onCollisionTime = 0;


    int killCount_;
    int jewelDeliver_;

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

    void OnCollision(GameObject* pTarget)override;

    int SendJewel(){ return jewelDeliver_; }
    int GetJewelCount() { return jewelCount_; }

    void KillCountUp() { killCount_++; }
    int GetKillCount() { return killCount_; }
};

