#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"
//#include "PlayerState.h"


class Stage;

class Player :public GameObject
{
private:

    int hModel_;
    int hStage_;
    int hEnemy_;

    bool isJumping = false;

   // PlayerState* currentState_;
   // PlayerCamera camera_;

    float moveY_ = 0;

    float jewelCount_;  //持っている宝石の数
    float weight_;
    int killCount_;
    int jewelDeliver_;  //運んだ宝石の数

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //void ChangeState(PlayerState* newState);

    void OnCollision(GameObject* pTarget)override;


    XMFLOAT3 GetPlayerPos() { return transform_.position_; };

    XMVECTOR GetPlayerVec();

    // ゲッターとセッター
   // PlayerCamera& GetCamera() { return camera_; }
    int GetModelHandle() const { return hModel_; }

    int SendJewel() { return jewelDeliver_; };        //宝石箱に納品した宝石の数を送ります
    int GetJewelCount();    //今手に持っている宝石の数を返します

    void KillCountUp();     //プレイヤーが直接敵を倒した数を1増やします
    int GetKillCount();     //プレイヤーが直接倒した敵の数を返します。

    void SetVelocityY(float _vY) { moveY_ = _vY; };
    float GetVelocityY() { return moveY_; };
    void SetVelocityX(float _vX) {}
    float GetVelocityX() { return 0.0f; }

    void SetJumping(bool _flag) { isJumping = _flag; }

    void SetMoveY(float _moveY) { transform_.position_.y += _moveY; }

    XMVECTOR GetKnockbackDirection();

    int GetStageHandle() { return hStage_; }
};