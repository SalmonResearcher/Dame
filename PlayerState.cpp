// PlayerState.cpp
#include "PlayerState.h"
#include "Player.h"
#include "StateManager.h"
#include "InputManager.h"

#include "Engine/Input.h"
#include "Engine/Model.h" // Model::RayCastData の定義を仮定


// 待機
IdleState::IdleState(StateManager* manager): StateBase(manager),pPlayer_(nullptr),idle{0,120,1}
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

//待機開始
void IdleState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), idle.startframe, idle.endframe, idle.speed);// 待機animationのフレーム
}

// 待機状態の更新処理
void IdleState::UpdateState()
{

    // ジャンプ
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // 歩き
    if (InputManager::IsWalk()) { pStateManager_->ChangeState("WalkState"); }

    // 攻撃
    if (InputManager::IsAttack()) { pStateManager_->ChangeState("AttackState"); }
}

void IdleState::ExitState()
{
}


// 歩き
WalkState::WalkState(StateManager* manager):StateBase(manager),pPlayer_(nullptr),walk{ 140,230,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void WalkState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), walk.startframe, walk.endframe, walk.speed); // 歩行アニメーションのフレーム設定
}

void WalkState::UpdateState()
{
    pPlayer_->Walk();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // ダッシュキーが押されたら
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunState"); }

    // 移動入力がなくなったとき待機へ
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
    
    // 攻撃
    if (InputManager::IsAttack()) { pStateManager_->ChangeState("AttackState"); }
}

void WalkState::ExitState()
{
    // 必要に応じて終了処理
}

// RunState

JumpState::JumpState(StateManager* manager):StateBase(manager),pPlayer_(nullptr)
// JumpState
void JumpState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ジャンプアニメーションのフレーム設定

    // ジャンプの初期速度を設定
    player->SetVelocityY(0.2f);
}

void JumpState::UpdateState()
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

void JumpState::ExitState()
{
    // 必要に応じて終了処理
}

// AttackState
void AttackState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ジャンプアニメーションのフレーム設定

    // ジャンプの初期速度を設定
    player->SetVelocityY(0.2f);
}

void AttackState::UpdateState()
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

void AttackState::ExitState()
{
    // 必要に応じて終了処理
}

//RunState
void RunState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 340, 365, 1); // ダッシュアニメーションのフレーム設定
}

void RunState::UpdateState()
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

void RunState::ExitState()
{
    // ダッシュステートから出る時の処理
}

// FallState
void FallState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 230, 280, 1); // 落下アニメーションのフレーム設定
}

void FallState::UpdateState()
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

void FallState::ExitState()
{
    // 必要に応じて終了処理
}

// KnockbackState
void KnockbackState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // ノックバックアニメーションのフレーム設定

    // ノックバックの初期速度を設定
    player->SetVelocityX(-0.3f); // X方向にノックバックする例
}

void KnockbackState::UpdateState()
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

void KnockbackState::ExitState()
{
    // ノックバックステートを終了する際の処理（必要に応じて）
}

