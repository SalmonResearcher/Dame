// PlayerState.cpp
#include "PlayerState.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h" // Model::RayCastData �̒�`������

namespace
{
}

bool PlayerState::IsGrounded(Player* player)
{
    RayCastData data;
    data.start = { player->GetPosition().x, 0, player->GetPosition().z };
    data.dir = XMFLOAT3(0, -1, 0);

    Model::RayCast(player->GetStageHandle(), &data); // ���C�𔭎˂��Đڒn������擾

    return data.hit && data.dist < 0.25f; // �n�ʂɃq�b�g���Ă���A�������������l�����Ȃ�ΐڒn���Ă���Ɣ���
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
    // �A�C�h����Ԃ̍X�V����
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
    // �A�C�h����Ԃ���o�鎞�̏���
}

// WalkState
void WalkState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 140, 230, 1); // ���s�A�j���[�V�����̃t���[���ݒ�
}

void WalkState::Update(Player* player)
{
    // �ړ�����
    XMVECTOR move = XMVectorZero();
    if (Input::IsKey(DIK_W)) move += XMVectorSet(0, 0, 1, 0);
    if (Input::IsKey(DIK_S)) move += XMVectorSet(0, 0, -1, 0);
    if (Input::IsKey(DIK_A)) move += XMVectorSet(-1, 0, 0, 0);
    if (Input::IsKey(DIK_D)) move += XMVectorSet(1, 0, 0, 0);

    if (XMVectorGetX(XMVector3LengthSq(move)) > 0)
    {
        move = XMVector3Normalize(move);
        XMFLOAT3 pos = player->GetPosition();
        XMStoreFloat3(&pos, XMLoadFloat3(&pos) + move * 0.1f); // �ړ����x�𒲐�
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
    // �K�v�ɉ����ďI������
}

// RunState


// JumpState
void JumpState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �W�����v�A�j���[�V�����̃t���[���ݒ�

    // �W�����v�̏������x��ݒ�
    player->SetVelocityY(0.2f);
}

void JumpState::Update(Player* player)
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

void JumpState::Exit(Player* player)
{
    // �K�v�ɉ����ďI������
}

// AttackState
void AttackState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �W�����v�A�j���[�V�����̃t���[���ݒ�

    // �W�����v�̏������x��ݒ�
    player->SetVelocityY(0.2f);
}

void AttackState::Update(Player* player)
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

void AttackState::Exit(Player* player)
{
    // �K�v�ɉ����ďI������
}

//RunState
void RunState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 340, 365, 1); // �_�b�V���A�j���[�V�����̃t���[���ݒ�
}

void RunState::Update(Player* player)
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

void RunState::Exit(Player* player)
{
    // �_�b�V���X�e�[�g����o�鎞�̏���
}

// FallState
void FallState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 230, 280, 1); // �����A�j���[�V�����̃t���[���ݒ�
}

void FallState::Update(Player* player)
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

void FallState::Exit(Player* player)
{
    // �K�v�ɉ����ďI������
}

// KnockbackState
void KnockbackState::Enter(Player* player)
{
    int hModel = player->GetModelHandle();
    Model::SetAnimFrame(hModel, 280, 330, 1); // �m�b�N�o�b�N�A�j���[�V�����̃t���[���ݒ�

    // �m�b�N�o�b�N�̏������x��ݒ�
    player->SetVelocityX(-0.3f); // X�����Ƀm�b�N�o�b�N�����
}

void KnockbackState::Update(Player* player)
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

void KnockbackState::Exit(Player* player)
{
    // �m�b�N�o�b�N�X�e�[�g���I������ۂ̏����i�K�v�ɉ����āj
}


