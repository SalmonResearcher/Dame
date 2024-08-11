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
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), idle.startframe, idle.endframe, idle.speed);// 待機アニメーションのフレーム
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
WalkState::WalkState(StateManager* manager):StateBase(manager),pPlayer_(nullptr),walk{ 280,330,1 }
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

// JumpState
JumpState::JumpState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr), jump{ 400, 460, 1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void JumpState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), jump.startframe, jump.endframe, jump.speed); // ジャンプアニメーションのフレーム設定
}

void JumpState::UpdateState()
{
    if (InputManager::IsJump() && !pPlayer_->IsJumping())
    {
        pPlayer_->Jump();
    }


    // 攻撃入力があった場合のステート遷移
    if (InputManager::IsAttack())
    {
        pStateManager_->ChangeState("AttackState");
    }

    else if (InputManager::IsWalk())
    {
        pStateManager_->ChangeState("WalkState");
    }

    // ジャンプが終了したらアイドルステートに遷移
    else if (!pPlayer_->IsJumping())
    {
        pStateManager_->ChangeState("IdleState");
    }
}

void JumpState::ExitState()
{
    // 必要に応じて終了処理
}

// AttackState
AttackState::AttackState(StateManager* manager) :StateBase(manager), attack{370,390,1}
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}
void AttackState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),attack.startframe,attack.endframe,attack.speed); // 攻撃アニメーションのフレーム設定
}

void AttackState::UpdateState()
{
    pPlayer_->Attacking();
    if (pPlayer_->IsAttackEnd())
    {
        pStateManager_->ChangeState("IdleState");
    }
}

void AttackState::ExitState()
{
    // 必要に応じて終了処理
}

//RunState
RunState::RunState(StateManager* manager) :StateBase(manager), run{ 340,365,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void RunState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),run.startframe,run.endframe,run.speed); // ダッシュアニメーションのフレーム設定
}

void RunState::UpdateState()
{
    pPlayer_->Run();

    // ジャンプキーが押されたら
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // 移動入力がなくなったとき待機へ
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }

    if (InputManager::IsAttack())
    {
        pStateManager_->ChangeState("AttackState");
    }
}

void RunState::ExitState()
{
    // ダッシュステートから出る時の処理
}

// KnockbackState
KnockbackState::KnockbackState(StateManager* manager) : StateBase(manager), knock{ 400,460,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void KnockbackState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),knock.startframe,knock.endframe,knock.speed); // ノックバックアニメーションのフレーム設定
}

void KnockbackState::UpdateState()
{
    pPlayer_->Knockback();

    if (pPlayer_->IsJumping()) { pStateManager_->ChangeState("IdleState"); }
}

void KnockbackState::ExitState()
{
    // ノックバックステートを終了する際の処理（必要に応じて）
}

