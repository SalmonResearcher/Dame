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
    // �v���C���[���A�C�h����Ԃɓ������Ƃ��̏���
    // ��F�A�C�h���A�j���[�V�����̊J�n
    // player->PlayAnimation("Idle");
}

void IdleState::Update(Player* player)
{
    // �v���C���[�̌��݈ʒu���擾
    XMFLOAT3 currentPos = player->GetPosition();

    // �n�ʂƂ̐ڒn����
    float groundHeight = GetGroundHeight(currentPos, player);
    currentPos.y = groundHeight + player->GetHeight() / 2;  // �v���C���[�̒��S���n�ʏ�ɂȂ�悤�ɒ���

    player->SetPosition(currentPos);

    // ��ԑJ�ڂ̃`�F�b�N
    CheckStateTransition(player);
}

void IdleState::Exit(Player* player)
{
    // �A�C�h����Ԃ𔲂���Ƃ��̏���
    // ��F�A�C�h���A�j���[�V�����̒�~
    // player->StopAnimation("Idle");
}

void IdleState::CheckStateTransition(Player* player)
{
    // �ړ��L�[�������ꂽ��ړ���Ԃ�
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
    {
        player->ChangeState(new MovingState());
    }
    // �W�����v�L�[�������ꂽ��W�����v��Ԃ�
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpingState());
    }
    // ���̑��̏�ԑJ�ڏ�����ǉ�
}

float IdleState::GetGroundHeight(const XMFLOAT3& position, Player* player)
{
    RayCastData down;
    down.start = { position.x, position.y + 1.0f, position.z };  // �v���C���[�̏����ォ�甭��
    down.dir = XMFLOAT3(0, -1, 0);  // �������ɔ���

    // ���C�L���X�g�����s
    Model::RayCast(player->GetStageHandle(), &down);

    if (down.hit)
    {
        // ���C���n�ʂɓ��������ꍇ�A���̍�����Ԃ�
        return down.start.y - down.dist;
    }
    else
    {
        // ���C��������Ȃ������ꍇ�̃f�t�H���g�l�i��F���ɒႢ�l�j
        return -1000.0f;
    }
}