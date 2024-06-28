// PlayerState.h
#pragma once
#include "Engine/GameObject.h"

class Player;

struct AnimFrame
{
    int startframe;
    int endframe;
    int speed;
};


class PlayerState {
    Player* pPlayer_;
    
public:
    virtual ~PlayerState() {}
    virtual void Enter(Player* player) = 0;
    virtual void Update(Player* player) = 0;
    virtual void Exit(Player* player) = 0;

protected:
    bool IsGrounded(Player* player);//接地しているかどうか
};

class IdleState : public PlayerState {
    AnimFrame idle = {0,120,1};
    Player* pPlayer_;
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};

class WalkState : public PlayerState {
    AnimFrame walk
    Player* pPlayer_;
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};

class RunState : public PlayerState {
    Player* pPlayer_;
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};

class JumpState : public PlayerState {
    Player* pPlayer_;
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};

class AttackState : public PlayerState {
    Player* pPlayer_;
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};

class KnockbackState : public PlayerState {
    Player* pPlayer_;
private:
    float knockbackStrength = 0.8f; // ノックバックの強さ
    float jumpHeight = 0.1f;        // ノックバック時のジャンプ高さ

public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;
};