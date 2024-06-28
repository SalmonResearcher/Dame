//// PlayerState.h
//#pragma once
//#include "Engine/GameObject.h"
//
//class Player;
//
//class PlayerState {
//public:
//    virtual ~PlayerState() {}
//    virtual void Enter(Player* player) = 0;
//    virtual void Update(Player* player) = 0;
//    virtual void Exit(Player* player) = 0;
//
//protected:
//    bool IsGrounded(Player* player);//�ڒn���Ă��邩�ǂ���
//};
//
//class IdleState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class WalkState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class RunState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class JumpState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class AttackState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class FallState : public PlayerState {
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};
//
//class KnockbackState : public PlayerState {
//private:
//    float knockbackStrength = 0.8f; // �m�b�N�o�b�N�̋���
//    float jumpHeight = 0.1f;        // �m�b�N�o�b�N���̃W�����v����
//
//public:
//    void Enter(Player* player) override;
//    void Update(Player* player) override;
//    void Exit(Player* player) override;
//};