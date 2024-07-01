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
    Model::SetAnimFrame(pPlayer_->GetModelHandle(), idle.startframe, idle.endframe, idle.speed);// �ҋ@animation�̃t���[��
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
WalkState::WalkState(StateManager* manager):StateBase(manager),pPlayer_(nullptr),walk{ 140,230,1 }
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

// RunState

JumpState::JumpState(StateManager* manager):StateBase(manager),pPlayer_(nullptr)
// JumpState
void JumpState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �W�����v�A�j���[�V�����̃t���[���ݒ�

    // �W�����v�̏������x��ݒ�
    player->SetVelocityY(0.2f);
}

void JumpState::UpdateState()
{
    // �d�͂�K�p
    float velocityY = player->GetVelocityY();
    velocityY -= 0.01f; // �d�͉����x
    player->SetVelocityY(velocityY);

    // Y���W���X�V
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // �n�ʂɒ��n�������`�F�b�N
    if (IsGrounded(player)) // IsGrounded ���g�p���Đڒn������s��
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }

    // �󒆂ł̐����ړ�
    // WalkState�̈ړ��������ȗ������ēK�p
}

void JumpState::ExitState()
{
    // �K�v�ɉ����ďI������
}

// AttackState
void AttackState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �W�����v�A�j���[�V�����̃t���[���ݒ�

    // �W�����v�̏������x��ݒ�
    player->SetVelocityY(0.2f);
}

void AttackState::UpdateState()
{
    // �d�͂�K�p
    float velocityY = player->GetVelocityY();
    velocityY -= 0.01f; // �d�͉����x
    player->SetVelocityY(velocityY);

    // Y���W���X�V
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // �n�ʂɒ��n�������`�F�b�N
    if (pos.y <= 0) // �n�ʂ�Y���W��0�Ɖ���
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }

    // �󒆂ł̐����ړ�
    // WalkState�̈ړ��������ȗ������ēK�p
}

void AttackState::ExitState()
{
    // �K�v�ɉ����ďI������
}

//RunState
void RunState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 340, 365, 1); // �_�b�V���A�j���[�V�����̃t���[���ݒ�
}

void RunState::UpdateState()
{
    // �_�b�V�����̈ړ������⑬�x�̒����Ȃǂ���������
    XMVECTOR move = XMVectorZero();
    if (Input::IsKey(DIK_W)) move += XMVectorSet(0, 0, 1, 0);
    if (Input::IsKey(DIK_S)) move += XMVectorSet(0, 0, -1, 0);
    if (Input::IsKey(DIK_A)) move += XMVectorSet(-1, 0, 0, 0);
    if (Input::IsKey(DIK_D)) move += XMVectorSet(1, 0, 0, 0);

    if (XMVectorGetX(XMVector3LengthSq(move)) > 0)
    {
        move = XMVector3Normalize(move);
        XMFLOAT3 pos = player->GetPosition();
        XMStoreFloat3(&pos, XMLoadFloat3(&pos) + move * 0.2f); // �_�b�V�����̈ړ����x�𒲐�
        player->SetPosition(pos);
    }
    else
    {
        player->ChangeState(new IdleState());
    }

    // �_�b�V���̏I�������𔻒肷��i��F�_�b�V���L�[�𗣂�����IdleState�ɑJ�ځj
    if (!Input::IsKey(DIK_LSHIFT))
    {
        player->ChangeState(new IdleState());
    }
}

void RunState::ExitState()
{
    // �_�b�V���X�e�[�g����o�鎞�̏���
}

// FallState
void FallState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 230, 280, 1); // �����A�j���[�V�����̃t���[���ݒ�
}

void FallState::UpdateState()
{
    // �d�͂�K�p
    float velocityY = player->GetVelocityY();
    velocityY -= 0.02f; // �d�͉����x�𒲐�
    player->SetVelocityY(velocityY);

    // Y���W���X�V
    XMFLOAT3 pos = player->GetPosition();
    pos.y += velocityY;
    player->SetPosition(pos);

    // �n�ʂɒ��n�������`�F�b�N
    if (pos.y <= 0) // �n�ʂ�Y���W��0�Ɖ���
    {
        pos.y = 0;
        player->SetPosition(pos);
        player->ChangeState(new IdleState());
    }
}

void FallState::ExitState()
{
    // �K�v�ɉ����ďI������
}

// KnockbackState
void KnockbackState::EnterState()
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �m�b�N�o�b�N�A�j���[�V�����̃t���[���ݒ�

    // �m�b�N�o�b�N�̏������x��ݒ�
    player->SetVelocityX(-0.3f); // X�����Ƀm�b�N�o�b�N�����
}

void KnockbackState::UpdateState()
{
    // �m�b�N�o�b�N�����̎��{
    XMVECTOR knockbackDirection = player->GetKnockbackDirection(); // �m�b�N�o�b�N�������擾
    XMVECTOR knockbackVelocity = knockbackDirection * knockbackStrength * 0.1f; // �m�b�N�o�b�N���x�̌v�Z

    // �v���C���[�̈ʒu���X�V
    XMVECTOR currentPosition = XMLoadFloat3(&player->GetPosition());
    XMVECTOR newPosition = currentPosition + knockbackVelocity;
    XMStoreFloat3(&player->GetPosition(), newPosition);

    // �m�b�N�o�b�N���̃W�����v�ݒ�
    player->SetJumping(true);
    player->SetMoveY(jumpHeight);

    // �m�b�N�o�b�N���I��������A�Ⴆ�Ύ��Ԍo�߂����̏����𖞂������玟�̃X�e�[�g�ɑJ�ڂ�����
    // �����ł͊ȒP��IdleState�ɖ߂��������
    if (IsGrounded(player)) {
        player->ChangeState(new IdleState());
    }
}

void KnockbackState::ExitState()
{
    // �m�b�N�o�b�N�X�e�[�g���I������ۂ̏����i�K�v�ɉ����āj
}

