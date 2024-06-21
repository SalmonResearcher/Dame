// IdleState.h
#pragma once
#include "PlayerState.h"
#include "Engine/Input.h"
#include <DirectXMath.h>

class Player;
class MovingState;
class JumpingState;

class IdleState : public PlayerState
{
public:
    void Enter(Player* player) override;
    void Update(Player* player) override;
    void Exit(Player* player) override;

private:
    void CheckStateTransition(Player* player);
    float GetGroundHeight(const DirectX::XMFLOAT3& position, Player* player);
};

// IdleState.cpp
#include "IdleState.h"
#include "Player.h"
#include "MovingState.h"
#include "JumpingState.h"
#include "Engine/Model.h"

using namespace DirectX;

void IdleState::Enter(Player* player)
{
    // プレイヤーがアイドル状態に入ったときの処理
    // 例：アイドルアニメーションの開始
    // player->PlayAnimation("Idle");
}

void IdleState::Update(Player* player)
{
    // プレイヤーの現在位置を取得
    XMFLOAT3 currentPos = player->GetPosition();

    // 地面との接地処理
    float groundHeight = GetGroundHeight(currentPos, player);
    currentPos.y = groundHeight + player->GetHeight() / 2;  // プレイヤーの中心が地面上になるように調整

    player->SetPosition(currentPos);

    // 状態遷移のチェック
    CheckStateTransition(player);
}

void IdleState::Exit(Player* player)
{
    // アイドル状態を抜けるときの処理
    // 例：アイドルアニメーションの停止
    // player->StopAnimation("Idle");
}

void IdleState::CheckStateTransition(Player* player)
{
    // 移動キーが押されたら移動状態へ
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
    {
        player->ChangeState(new MovingState());
    }
    // ジャンプキーが押されたらジャンプ状態へ
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpingState());
    }
    // その他の状態遷移条件を追加
}

float IdleState::GetGroundHeight(const XMFLOAT3& position, Player* player)
{
    RayCastData down;
    down.start = { position.x, position.y + 1.0f, position.z };  // プレイヤーの少し上から発射
    down.dir = XMFLOAT3(0, -1, 0);  // 下向きに発射

    // レイキャストを実行
    Model::RayCast(player->GetStageHandle(), &down);

    if (down.hit)
    {
        // レイが地面に当たった場合、その高さを返す
        return down.start.y - down.dist;
    }
    else
    {
        // レイが当たらなかった場合のデフォルト値（例：非常に低い値）
        return -1000.0f;
    }
}