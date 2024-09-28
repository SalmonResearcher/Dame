#include "InputManager.h"

namespace InputManager
{
	// キーボード入力
	constexpr int  MOVE_FORWARD_KEY = DIK_W;      // 前進
	constexpr int  MOVE_LEFT_KEY = DIK_A;        // 左移動
	constexpr int  MOVE_BACKWARD_KEY = DIK_S;     // 後退
	constexpr int  MOVE_RIGHT_KEY = DIK_D;        // 右移動
	constexpr int  JUMP_KEY = DIK_SPACE;          // ジャンプ
	constexpr int  RUN_KEY = DIK_LSHIFT;          // 走る
	constexpr int  MENU_KEY = DIK_ESCAPE;         // メニュー
	constexpr int  ACTION_KEY = DIK_E;      // イベントアクション

	// マウス入力
	constexpr int  MOUSE_LEFT = 0;                        // マウス左ボタン
	constexpr int  MOUSE_RIGHT = 1;                       // マウス右ボタン
	constexpr int  ATTACK_KEY = MOUSE_LEFT;                // 射撃
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

