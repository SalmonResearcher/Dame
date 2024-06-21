#pragma once
#include "PlayerState.h"
class AttackingState : public PlayerState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};