// PlayerState.cpp
#include "PlayerState.h"
#include "Player.h"
#include "StateManager.h"
#include "InputManager.h"

#include "Engine/Input.h"
#include "Engine/Model.h" // Model::RayCastData �̒�`������


// �ҋ@
IdleState::IdleState(StateManager* manager): StateBase(manager),pPlayer_(nullptr),idle{0,120,1}
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

//�ҋ@�J�n
void IdleState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), idle.startframe, idle.endframe, idle.speed);// �ҋ@�A�j���[�V�����̃t���[��
}

// �ҋ@��Ԃ̍X�V����
void IdleState::UpdateState()
{

    // �W�����v
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // ����
    if (InputManager::IsWalk()) { pStateManager_->ChangeState("WalkState"); }

    // �U��
    if (InputManager::IsAttack()) { pStateManager_->ChangeState("AttackState"); }
}

void IdleState::ExitState()
{
}


// ����
WalkState::WalkState(StateManager* manager):StateBase(manager),pPlayer_(nullptr),walk{ 280,330,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void WalkState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), walk.startframe, walk.endframe, walk.speed); // ���s�A�j���[�V�����̃t���[���ݒ�
}

void WalkState::UpdateState()
{

    pPlayer_->Walk();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // �_�b�V���L�[�������ꂽ��
    if (InputManager::IsRun()) { pStateManager_->ChangeState("RunState"); }

    // �ړ����͂��Ȃ��Ȃ����Ƃ��ҋ@��
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }
    
    // �U��
    if (InputManager::IsAttack()) { pStateManager_->ChangeState("AttackState"); }
}

void WalkState::ExitState()
{
    // �K�v�ɉ����ďI������
}

// JumpState
JumpState::JumpState(StateManager* manager) : StateBase(manager), pPlayer_(nullptr), jump{ 400, 460, 1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void JumpState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), jump.startframe, jump.endframe, jump.speed); // �W�����v�A�j���[�V�����̃t���[���ݒ�
}

void JumpState::UpdateState()
{
    if (InputManager::IsJump() && !pPlayer_->IsJumping())
    {
        pPlayer_->Jump();
    }


    // �U�����͂��������ꍇ�̃X�e�[�g�J��
    if (InputManager::IsAttack())
    {
        pStateManager_->ChangeState("AttackState");
    }

    else if (InputManager::IsWalk())
    {
        pStateManager_->ChangeState("WalkState");
    }

    // �W�����v���I��������A�C�h���X�e�[�g�ɑJ��
    else if (!pPlayer_->IsJumping())
    {
        pStateManager_->ChangeState("IdleState");
    }
}

void JumpState::ExitState()
{
    // �K�v�ɉ����ďI������
}

// AttackState
AttackState::AttackState(StateManager* manager) :StateBase(manager), attack{370,390,1}
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}
void AttackState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),attack.startframe,attack.endframe,attack.speed); // �U���A�j���[�V�����̃t���[���ݒ�
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
    // �K�v�ɉ����ďI������
}

//RunState
RunState::RunState(StateManager* manager) :StateBase(manager), run{ 340,365,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void RunState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),run.startframe,run.endframe,run.speed); // �_�b�V���A�j���[�V�����̃t���[���ݒ�
}

void RunState::UpdateState()
{
    pPlayer_->Run();

    // �W�����v�L�[�������ꂽ��
    if (InputManager::IsJump()) { pStateManager_->ChangeState("JumpState"); }

    // �ړ����͂��Ȃ��Ȃ����Ƃ��ҋ@��
    if (!InputManager::IsWalk()) { pStateManager_->ChangeState("IdleState"); }

    if (InputManager::IsAttack())
    {
        pStateManager_->ChangeState("AttackState");
    }
}

void RunState::ExitState()
{
    // �_�b�V���X�e�[�g����o�鎞�̏���
}

// KnockbackState
KnockbackState::KnockbackState(StateManager* manager) : StateBase(manager), knock{ 400,460,1 }
{
    pPlayer_ = static_cast<Player*>(pStateManager_->GetGameObject());
}

void KnockbackState::EnterState()
{
    Model::SetAnimFrame(pPlayer_->GetModelHandle(),knock.startframe,knock.endframe,knock.speed); // �m�b�N�o�b�N�A�j���[�V�����̃t���[���ݒ�
}

void KnockbackState::UpdateState()
{
    pPlayer_->Knockback();

    if (pPlayer_->IsJumping()) { pStateManager_->ChangeState("IdleState"); }
}

void KnockbackState::ExitState()
{
    // �m�b�N�o�b�N�X�e�[�g���I������ۂ̏����i�K�v�ɉ����āj
}

