#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Engine/Input.h"

class JumpingState;
class IdleState;


class MovingState : public PlayerState
{
private:
    float speed_;
    const float MAX_SPEED = 0.15f;
    const float ACCELERATION = 0.01f;
    const float DECELERATION = 0.01f;

public:
    void Enter(Player* player) override
    {
        speed_ = 0.0f;
    }

    void Update(Player* _player) override
    {
        // �ړ�����
        XMVECTOR moveVector = CalculateMoveVector(_player);

        // ���x�̍X�V
        UpdateSpeed();

        // �v���C���[�̈ʒu���X�V
        XMVECTOR playerPos = XMLoadFloat3(&_player->GetPlayerPos());
        playerPos += moveVector * speed_;
        XMFLOAT3 newPos;
        XMStoreFloat3(&newPos, playerPos);
        _player->SetPosition(newPos);

        // ��ԑJ�ڂ̃`�F�b�N
        CheckStateTransition(_player);
    }

    void Exit(Player* player) override
    {
        // �K�v�ɉ����ďI���������L�q
    }

private:
    XMVECTOR CalculateMoveVector(Player* player)
    {
        XMVECTOR moveVector = XMVectorZero();
        if (Input::IsKey(DIK_W)) moveVector += player->GetForwardVector();
        if (Input::IsKey(DIK_S)) moveVector -= player->GetForwardVector();
        if (Input::IsKey(DIK_A)) moveVector -= player->GetRightVector();
        if (Input::IsKey(DIK_D)) moveVector += player->GetRightVector();

        return XMVector3Normalize(moveVector);
    }

    void UpdateSpeed()
    {
        if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
        {
            speed_ += ACCELERATION;
            if (speed_ > MAX_SPEED) speed_ = MAX_SPEED;
        }
        else
        {
            speed_ -= DECELERATION;
            if (speed_ < 0.0f) speed_ = 0.0f;
        }
    }

    void CheckStateTransition(Player* player)
    {
        if (speed_ == 0.0f)
        {
            player->ChangeState(new IdleState());
        }
        else if (Input::IsKeyDown(DIK_SPACE))
        {
            player->ChangeState(new JumpingState());
        }
        // ���̏�ԑJ�ڏ����������ɒǉ�
    }
};