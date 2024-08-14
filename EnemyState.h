#pragma once
#include "Engine/GameObject.h"
#include "StateBase.h"

struct AnimFrame
{
    int startframe;
    int endframe;
    int speed;
};
    
class WalkState : public StateBase {
    AnimFrame walk;
    Enemy* pEnemy_;
public:
    WalkState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class AttackState : public StateBase {
    AnimFrame attack;
    Enemy* pEnemy_;
public:
    AttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class DeadState : public StateBase {
    AnimFrame dead;
    Enemy* pEnemy_;
public:
    DeadState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};