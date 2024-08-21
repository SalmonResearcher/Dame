#pragma once
#include "Engine/GameObject.h"
#include "StateBase.h"

class Enemy;

struct AnimFrame
{
    int startframe;
    int endframe;
    int speed;
};
    
class EnemyWalkState : public StateBase {
    AnimFrame walk;
    Enemy* pEnemy_;
public:
    EnemyWalkState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class EnemyAttackState : public StateBase {
    AnimFrame attack;
    Enemy* pEnemy_;
public:
    EnemyAttackState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};

class EnemyDeadState : public StateBase {
    AnimFrame dead;
    Enemy* pEnemy_;
public:
    EnemyDeadState(StateManager* manager);
    void EnterState() override;
    void UpdateState() override;
    void ExitState() override;
};