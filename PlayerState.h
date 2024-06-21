#pragma once

class Player;

//�v���C���[�X�e�[�g�̊��N���X
class PlayerState{
public:
    //�ύX���ꂽ�Ƃ��ɔ���
    virtual void Enter(Player* _pPlayer) = 0;
    //�X�V
    virtual void Update(Player* _pPlayer) = 0;

    virtual void HandleInput(Player* _pPlayer) = 0;

    //�I���Ƃ��ɔ����i�A�j���[�V�����Ȃǁj
    virtual void Exit(Player* _pPlayer) = 0;

    //��ԕω�
    void Changestate(PlayerState* _nowState, PlayerState* _state);
};