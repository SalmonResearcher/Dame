#include "InputManager.h"

namespace InputManager
{
	// �L�[�{�[�h����
	constexpr int  MOVE_FORWARD_KEY = DIK_W;      // �O�i
	constexpr int  MOVE_LEFT_KEY = DIK_A;        // ���ړ�
	constexpr int  MOVE_BACKWARD_KEY = DIK_S;     // ���
	constexpr int  MOVE_RIGHT_KEY = DIK_D;        // �E�ړ�
	constexpr int  JUMP_KEY = DIK_SPACE;          // �W�����v
	constexpr int  RUN_KEY = DIK_LSHIFT;          // ����
	constexpr int  MENU_KEY = DIK_ESCAPE;         // ���j���[
	constexpr int  ACTION_KEY = DIK_E;      // �C�x���g�A�N�V����

	// �}�E�X����
	constexpr int  MOUSE_LEFT = 0;                        // �}�E�X���{�^��
	constexpr int  MOUSE_RIGHT = 1;                       // �}�E�X�E�{�^��
	constexpr int  ATTACK_KEY = MOUSE_LEFT;                // �ˌ�
}

bool InputManager::IsShootJewel() { return Input::IsMouseButtonDown(MOUSE_LEFT) && IsAim(); }
bool InputManager::IsAim(){ return Input::IsMouseButton(MOUSE_RIGHT); }

bool InputManager::IsMoveForward() { return Input::IsKey(MOVE_FORWARD_KEY); }
bool InputManager::IsMoveLeft() { return Input::IsKey(MOVE_LEFT_KEY); }
bool InputManager::IsMoveRight() { return Input::IsKey(MOVE_RIGHT_KEY); }
bool InputManager::IsMoveBackward() { return Input::IsKey(MOVE_BACKWARD_KEY); }
bool InputManager::IsJump() { return Input::IsKeyDown(JUMP_KEY); }
bool InputManager::IsAttack() { return Input::IsMouseButtonDown(MOUSE_LEFT) && !(IsAim()); }
bool InputManager::IsWalk() { return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight(); }
bool InputManager::IsRun() { return Input::IsKey(RUN_KEY); }
bool InputManager::IsMenu() { return Input::IsKeyDown(MENU_KEY); }
bool InputManager::IsAction() { return Input::IsKeyDown(ACTION_KEY); }

