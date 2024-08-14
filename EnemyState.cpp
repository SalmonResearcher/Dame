#include "EnemyState.h"
#include "Enemy.h"
#include "StateManager.h"


// 歩き
WalkState::WalkState(StateManager* manager) :StateBase(manager), pEnemy_(nullptr), walk{ 0,100,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
}

void WalkState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), walk.startframe, walk.endframe, walk.speed); // 歩行アニメーションのフレーム設定
}

void WalkState::UpdateState()
{

    pEnemy_->Walk();

    // 攻撃
    if (pEnemy_->IsNearPlayer()) 
    {
        pStateManager_->ChangeState("AttackState"); 
    }
}

void WalkState::ExitState()
{
    // 必要に応じて終了処理
}

// AttackState
AttackState::AttackState(StateManager* manager) :StateBase(manager), attack{ 110,200,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
}
void AttackState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), attack.startframe, attack.endframe, attack.speed); // 攻撃アニメーションのフレーム設定
}

void AttackState::UpdateState()
{
    pEnemy_->Attack();
    if (pEnemy_->IsNearPlayer() == false)
    {
        pStateManager_->ChangeState("WalkState");
    }
}

void AttackState::ExitState()
{
    // 必要に応じて終了処理
}

DeadState::DeadState(StateManager* manager) :StateBase(manager), dead{210,}