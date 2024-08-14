#include "EnemyState.h"
#include "Enemy.h"
#include "StateManager.h"


// ����
WalkState::WalkState(StateManager* manager) :StateBase(manager), pEnemy_(nullptr), walk{ 0,100,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
}

void WalkState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), walk.startframe, walk.endframe, walk.speed); // ���s�A�j���[�V�����̃t���[���ݒ�
}

void WalkState::UpdateState()
{

    pEnemy_->Walk();

    // �U��
    if (pEnemy_->IsNearPlayer()) 
    {
        pStateManager_->ChangeState("AttackState"); 
    }
}

void WalkState::ExitState()
{
    // �K�v�ɉ����ďI������
}

// AttackState
AttackState::AttackState(StateManager* manager) :StateBase(manager), attack{ 110,200,1 }
{
    pEnemy_ = static_cast<Enemy*>(pStateManager_->GetGameObject());
}
void AttackState::EnterState()
{
    Model::SetAnimFrame(pEnemy_->GetModelHandle(), attack.startframe, attack.endframe, attack.speed); // �U���A�j���[�V�����̃t���[���ݒ�
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
    // �K�v�ɉ����ďI������
}

DeadState::DeadState(StateManager* manager) :StateBase(manager), dead{210,}