#include "MovingState.h"


// MovingState.cpp

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