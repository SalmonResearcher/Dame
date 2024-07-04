#pragma once
#include "Engine/Input.h"

// ���͏󋵂��Ǘ�����
namespace InputManager
{

    // ��΃V���b�g
    bool IsShootJewel();

    //�J�����̕���������
    bool IsAim();

    // �O�i
    bool IsMoveForward();

    // ���ړ�
    bool IsMoveLeft();

    // �E�ړ�
    bool IsMoveRight();

    // ���
    bool IsMoveBackward();



    // �ړ���
    bool IsWalk();

    // �����Ă���
    bool IsRun();

    // �W�����v��
    bool IsJump();

    // �U����
    bool IsAttack();

    // ���j���[���J���Ă���
    bool IsMenu();

    // �C�x���g�A�N�V����
    bool IsAction();

};