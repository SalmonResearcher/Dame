// StateBase.h
#pragma once
#include "Engine/GameObject.h"
#include "StateBase.h"

class Player;

struct AnimFrame
{
    int startframe;
    int endframe;
    int speed;
};

//bool IsGrounded()
//{
//    RayCastData data;
//    data.start = { player->GetPosition().x, 0, player->GetPosition().z };
//    data.dir = XMFLOAT3(0, -1, 0);
//
//    Model::RayCast(player->GetStageHandle(), &data); // レイを発射して接地判定を取得
//
//    return data.hit && data.dist < 0.25f; // 地面にヒットしており、距離がしきい値未満ならば接地していると判定
//}

class IdleState : public StateBase {
    AnimFrame idle;
    Player* pPlayer_;
public:
    IdleState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class WalkState : public StateBase {
    AnimFrame walk;
    Player* pPlayer_;
public:
    WalkState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class RunState : public StateBase {
    Player* pPlayer_;
public:
    RunState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class JumpState : public StateBase {
    Player* pPlayer_;
public:
    JumpState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class AttackState : public StateBase {
    Player* pPlayer_;
public:
    AttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class KnockbackState : public StateBase {
    Player* pPlayer_;
private:
    float knockbackStrength = 0.8f; // ノックバックの強さ
    float jumpHeight = 0.1f;        // ノックバック時のジャンプ高さ

public:
    KnockbackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};