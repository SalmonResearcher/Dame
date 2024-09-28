#pragma once
#include "Engine/Input.h"

// 入力状況を管理する
namespace InputManager
{

    // 宝石ショット
    bool IsShootJewel();

    //カメラの方向を向く
    bool IsAim();

    // 前進
    bool IsMoveForward();

    // 左移動
    bool IsMoveLeft();

    // 右移動
    bool IsMoveRight();

    // 後退
    bool IsMoveBackward();



    // 移動中
    bool IsWalk();

    // 走っている
    bool IsRun();

    // ジャンプ中
    bool IsJump();

    // 攻撃中
    bool IsAttack();

    // メニューを開いている
    bool IsMenu();

    // イベントアクション
    bool IsAction();

};