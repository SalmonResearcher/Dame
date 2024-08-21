#include "EnemyState.h"
#include "Enemy.h"
#include "StateManager.h"

#include "Engine/Debug.h"


// 歩き
EnemyWalkState::EnemyWalkState(StateManager* manager) :StateBase(manager), pEnemy_(nullptr), walk{ 0,100,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
}

void EnemyWalkState::EnterState()
{
    // 歩行アニメーションのフレーム設定
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), walk.startframe, walk.endframe, walk.speed); 
}

void EnemyWalkState::UpdateState()
{
    // 攻撃
    if (pEnemy_->IsNearPlayer())
    {
        pStateManager_->ChangeState("EnemyAttackState");
    }
    pEnemy_->Walk();

    if (pEnemy_->GetEnemyDeath())
    {
        pStateManager_->ChangeState("EnemyDeadState");
    }
}

void EnemyWalkState::ExitState()
{
    // 必要に応じて終了処理
}

// AttackState
EnemyAttackState::EnemyAttackState(StateManager* manager) :StateBase(manager), attack{ 110,200,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
    Debug::Log("AttackState", true);

}
void EnemyAttackState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), attack.startframe, attack.endframe, attack.speed); // 攻撃アニメーションのフレーム設定
    pEnemy_->SetAttackTime();
}

void EnemyAttackState::UpdateState()
{
    pEnemy_->Attack();

    if (pEnemy_->IsAttackEnd())
    {
        pStateManager_->ChangeState("EnemyWalkState");
    }
    if (pEnemy_->GetEnemyDeath())
    {
        pStateManager_->ChangeState("EnemyDeadState");
    }
}

void EnemyAttackState::ExitState()
{
    // 必要に応じて終了処理
}

//EnemyDeadState
EnemyDeadState::EnemyDeadState(StateManager* manager) :StateBase(manager), dead{ 210,400,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
    Debug::Log("DeadState", true);

}

void EnemyDeadState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), dead.startframe, dead.endframe, dead.speed);
}

void EnemyDeadState::UpdateState()
{
    pEnemy_->Dead();
}

void EnemyDeadState::ExitState()
{

}