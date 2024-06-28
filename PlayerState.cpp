// PlayerState.cpp
#include "PlayerState.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h" // Model::RayCastData の定義を仮定

namespace
{
}

bool PlayerState::IsGrounded(Player* player)
{
    RayCastData data;
    data.start = { player->GetPosition().x, 0, player->GetPosition().z };
    data.dir = XMFLOAT3(0, -1, 0);

    Model::RayCast(player->GetStageHandle(), &data); // レイを発射して接地判定を取得

    return data.hit && data.dist < 0.25f; // 地面にヒットしており、距離がしきい値未満ならば接地していると判定
}


// IdleState
void IdleState::Enter(Player* player)
{
    idle.
    int playerHandle_ = player->GetModelHandle();
    Model::SetAnimFrame(playerHandle_,)
}

void IdleState::Update(Player* player)
{
    // アイドル状態の更新処理
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
    {
        player->ChangeState(new WalkState());
    }
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpState());
    }
    else if (Input::IsMouseButtonDown(0))
    {
        player->ChangeState(new AttackState());
    }
}

void IdleState::Exit(Player* player)
{
    // アイドル状態から出る時の処理
}

// WalkState
void WalkState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 140, 230, 1); // 歩行アニメーションのフレーム設定
}

void WalkState::Update(Player* player)
{
    // 移動処理
    XMVECTOR move = XMVectorZero();
    if (Input::IsKey(DIK_W)) move += XMVectorSet(0, 0, 1, 0);
    if (Input::IsKey(DIK_S)) move += XMVectorSet(0, 0, -1, 0);
    if (Input::IsKey(DIK_A)) move += XMVectorSet(-1, 0, 0, 0);
    if (Input::IsKey(DIK_D)) move += XMVectorSet(1, 0, 0, 0);

    if (XMVectorGetX(XMVector3LengthSq(move)) > 0)
    {
        move = XMVector3Normalize(move);
        XMFLOAT3 pos = player->GetPosition();
        XMStoreFloat3(&pos, XMLoadFloat3(&pos) + move * 0.1f); // 移動速度を調整
        player->SetPosition(pos);
    }
    else
    {
        player->ChangeState(new IdleState());
    }

    if (Input::IsKey(DIK_LSHIFT))
    {
        player->ChangeState(new RunState());
    }
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpState());
    }
}

void WalkState::Exit(Player* player)
{
    // 必要に応じて終了処理
}

// RunState


// JumpState
void JumpState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ジャンプアニメーションのフレーム設定

    // ジャンプの初期速度を設定
    player->SetVelocityY(0.2f);
}

void JumpState::Update(Player* player)
{
    // 重力を適用
    float velocityY = player->GetVelocityY();
    velocityY -= 0.01f; // 重力加速度
    player->SetVelocityY(velocityY);

    // Y座標を更新
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // 地面に着地したかチェック
    if (IsGrounded(player)) // IsGrounded を使用して接地判定を行う
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }

    // 空中での水平移動
    // WalkStateの移動処理を簡略化して適用
}

void JumpState::Exit(Player* player)
{
    // 必要に応じて終了処理
}

// AttackState
void AttackState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ジャンプアニメーションのフレーム設定

    // ジャンプの初期速度を設定
    player->SetVelocityY(0.2f);
}

void AttackState::Update(Player* player)
{
    // 重力を適用
    float velocityY = player->GetVelocityY();
    velocityY -= 0.01f; // 重力加速度
    player->SetVelocityY(velocityY);

    // Y座標を更新
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // 地面に着地したかチェック
    if (pos.y <= 0) // 地面のY座標を0と仮定
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }

    // 空中での水平移動
    // WalkStateの移動処理を簡略化して適用
}

void AttackState::Exit(Player* player)
{
    // 必要に応じて終了処理
}

//RunState
void RunState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 340, 365, 1); // ダッシュアニメーションのフレーム設定
}

void RunState::Update(Player* player)
{
    // ダッシュ中の移動処理や速度の調整などを実装する
    XMVECTOR move = XMVectorZero();
    if (Input::IsKey(DIK_W)) move += XMVectorSet(0, 0, 1, 0);
    if (Input::IsKey(DIK_S)) move += XMVectorSet(0, 0, -1, 0);
    if (Input::IsKey(DIK_A)) move += XMVectorSet(-1, 0, 0, 0);
    if (Input::IsKey(DIK_D)) move += XMVectorSet(1, 0, 0, 0);

    if (XMVectorGetX(XMVector3LengthSq(move)) > 0)
    {
        move = XMVector3Normalize(move);
        XMFLOAT3 pos = player->GetPosition();
        XMStoreFloat3(&pos, XMLoadFloat3(&pos) + move * 0.2f); // ダッシュ中の移動速度を調整
        player->SetPosition(pos);
    }
    else
    {
        player->ChangeState(new IdleState());
    }

    // ダッシュの終了条件を判定する（例：ダッシュキーを離したらIdleStateに遷移）
    if (!Input::IsKey(DIK_LSHIFT))
    {
        player->ChangeState(new IdleState());
    }
}

void RunState::Exit(Player* player)
{
    // ダッシュステートから出る時の処理
}

// FallState
void FallState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 230, 280, 1); // 落下アニメーションのフレーム設定
}

void FallState::Update(Player* player)
{
    // 重力を適用
    float velocityY = player->GetVelocityY();
    velocityY -= 0.02f; // 重力加速度を調整
    player->SetVelocityY(velocityY);

    // Y座標を更新
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // 地面に着地したかチェック
    if (pos.y <= 0) // 地面のY座標を0と仮定
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }
}

void FallState::Exit(Player* player)
{
    // 必要に応じて終了処理
}

// KnockbackState
void KnockbackState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ノックバックアニメーションのフレーム設定

    // ノックバックの初期速度を設定
    player->SetVelocityX(-0.3f); // X方向にノックバックする例
}

void KnockbackState::Update(Player* player)
{
    // ノックバック処理の実施
    XMVECTOR knockbackDirection = player->GetKnockbackDirection(); // ノックバック方向を取得
    XMVECTOR knockbackVelocity = knockbackDirection * knockbackStrength * 0.1f; // ノックバック速度の計算

    // プレイヤーの位置を更新
    XMVECTOR currentPosition = XMLoadFloat3(&player->GetPosition());
    XMVECTOR newPosition = currentPosition + knockbackVelocity;
    XMStoreFloat3(&player->GetPosition(), newPosition);

    // ノックバック中のジャンプ設定
    player->SetJumping(true);
    player->SetMoveY(jumpHeight);

    // ノックバックが終了したら、例えば時間経過や特定の条件を満たしたら次のステートに遷移させる
    // ここでは簡単にIdleStateに戻す例を示す
    if (IsGrounded(player)) {
        player->ChangeState(new IdleState());
    }
}

void KnockbackState::Exit(Player* player)
{
    // ノックバックステートを終了する際の処理（必要に応じて）
}


