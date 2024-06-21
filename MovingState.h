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
        // 移動処理
        XMVECTOR moveVector = CalculateMoveVector(_player);

        // 速度の更新
        UpdateSpeed();

        // プレイヤーの位置を更新
        XMVECTOR playerPos = XMLoadFloat3(&_player->GetPlayerPos());
        playerPos += moveVector * speed_;
        XMFLOAT3 newPos;
        XMStoreFloat3(&newPos, playerPos);
        _player->SetPosition(newPos);

        // 状態遷移のチェック
        CheckStateTransition(_player);
    }

    void Exit(Player* player) override
    {
        // 必要に応じて終了処理を記述
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
        // 他の状態遷移条件をここに追加
    }
};