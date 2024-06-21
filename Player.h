#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Stage;
class PlayerState;

class Player :public GameObject
{
private:

    int hModel_;
    int hStage_;
    int hEnemy_;
    Stage* pStage_;    //ÉÇÉfÉãî‘çÜÇéÊìæ
    PlayerState* currentState_;

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void ChangeState(PlayerState* _newState);

    void StageRay();

    void OnCollision(GameObject* pTarget)override;


    XMVECTOR GetForwardVector() const;

    XMVECTOR GetRightVector() const;

    void SetPosition(const XMFLOAT3& position);




    XMFLOAT3 GetPlayerPos() { return transform_.position_; };

    XMVECTOR GetPlayerVec();

    int SendJewel();
    int GetJewelCount();

    void KillCountUp();
    int GetKillCount();

};