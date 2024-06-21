#pragma once
#include "PlayerState.h"

class JumpingState;
class IdleState;
class Player;

class MovingState : public PlayerState
{
private:
    float speed_;
    const float MAX_SPEED = 0.15f;
    const float ACCELERATION = 0.01f;
    const float DECELERATION = 0.01f;

public:

    void Enter(Player* player) override;
    void Update(Player* _player) override;
    void Exit(Player* player) override;

private:
    DirectX::XMVECTOR CalculateMoveVector(Player* player);
    void UpdateSpeed();
    void CheckStateTransition(Player* player);
    float GetGroundHeight(const DirectX::XMFLOAT3& position, Player* _player);
};
