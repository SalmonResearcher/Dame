#include "MovingState.h"
#include "Player.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "Engine/Input.h"


using namespace DirectX;

void MovingState::Enter(Player* player)
{
    speed_ = 0.0f;
}

void MovingState::Update(Player* _player)
{
    // �ړ�����
    XMVECTOR moveVector = CalculateMoveVector(_player);

    // ���x�̍X�V
    UpdateSpeed();

    // �v���C���[�̈ʒu���X�V
    XMVECTOR playerPos = XMLoadFloat3(&_player->GetPlayerPos());
    playerPos += moveVector * speed_;
    XMFLOAT3 newPos;
    XMStoreFloat3(&newPos, playerPos);
    _player->SetPosition(newPos);

    // ��ԑJ�ڂ̃`�F�b�N
    CheckStateTransition(_player);
}

void MovingState::Exit(Player* player)
{
    // �K�v�ɉ����ďI���������L�q
}

XMVECTOR MovingState::CalculateMoveVector(Player* player)
{
    XMVECTOR moveVector = XMVectorZero();
    if (Input::IsKey(DIK_W)) moveVector += player->GetForwardVector();
    if (Input::IsKey(DIK_S)) moveVector -= player->GetForwardVector();
    if (Input::IsKey(DIK_A)) moveVector -= player->GetRightVector();
    if (Input::IsKey(DIK_D)) moveVector += player->GetRightVector();

    return XMVector3Normalize(moveVector);
}

void MovingState::UpdateSpeed()
{
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
    {
        speed_ += ACCELERATION;
        if (speed_ > MAX_SPEED) speed_ = MAX_SPEED;
    }
    else
    {
        speed_ -= DECELERATION;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }
}

void MovingState::CheckStateTransition(Player* player)
{
    if (speed_ == 0.0f)
    {
        player->ChangeState(new IdleState());
    }
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpingState());
    }
    // ���̏�ԑJ�ڏ����������ɒǉ�
}

float MovingState::GetGroundHeight(const XMFLOAT3& position, Player* _player)
{
    // �n�ʂ̍������擾���郍�W�b�N�������ɒǉ�
    return 0.0f; // ���̎���
}


float MovingState::GetGroundHeight(const XMFLOAT3& position, Player* _player)
{
    RayCastData down;
    down.start = { position.x, position.y + 1.0f, position.z };  // �v���C���[�̏����ォ�甭��
    down.dir = XMFLOAT3(0, -1, 0);  // �������ɔ���

    // ���C�L���X�g�����s
    Model::RayCast(_player->GetStageHandle(), &down);

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

void MovingState::Update(Player* _player)
{
    // �ړ�����
    XMVECTOR moveVector = CalculateMoveVector(_player);

    // ���x�̍X�V
    UpdateSpeed();

    // �v���C���[�̈ʒu���X�V
    XMFLOAT3 currentPos = _player->GetPosition();
    XMVECTOR playerPos = XMLoadFloat3(&currentPos);
    playerPos += moveVector * speed_;

    XMFLOAT3 newPos;
    XMStoreFloat3(&newPos, playerPos);

    // �n�ʂƂ̐ڒn����
    float groundHeight = GetGroundHeight(newPos, _player);
    newPos.y = groundHeight + _player->GetHeight() / 2;  // �v���C���[�̒��S���n�ʏ�ɂȂ�悤�ɒ���

    _player->SetPosition(newPos);

    // ��ԑJ�ڂ̃`�F�b�N
    CheckStateTransition(_player);
}