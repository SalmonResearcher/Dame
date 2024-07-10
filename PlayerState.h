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
    AnimFrame run;
    Player* pPlayer_;
public:
    RunState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class JumpState : public StateBase {
    AnimFrame jump;
    Player* pPlayer_;
public:
    JumpState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class AttackState : public StateBase {
    AnimFrame attack;
    Player* pPlayer_;
public:
    AttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class KnockbackState : public StateBase {
    AnimFrame knock;
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