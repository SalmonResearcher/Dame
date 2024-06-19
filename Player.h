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
    Stage* pStage_;    //���f���ԍ����擾

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