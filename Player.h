#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "PlayerStateManager.h"

class Stage;

class Player :public GameObject
{
private:

    int hModel_;
    int hStage_;
    int hEnemy_;
    Stage* pStage_;    //ƒ‚ƒfƒ‹”Ô†‚ğæ“¾
    float jewelCount_;  //‚Á‚Ä‚¢‚é•óÎ‚Ì”
    float weight_;
    int killCount_;
    int jewelDeliver_;  //‰^‚ñ‚¾•óÎ‚Ì”

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void StageRay();

    void OnCollision(GameObject* pTarget)override;


    XMFLOAT3 GetPlayerPos() { return transform_.position_; };

    XMVECTOR GetPlayerVec();

    int SendJewel();
    int GetJewelCount();

    void KillCountUp();
    int GetKillCount();

};