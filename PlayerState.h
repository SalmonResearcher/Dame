#pragma once

class Player;

//プレイヤーステートの基底クラス
class PlayerState{
public:
    //変更されたときに発動
    virtual void Enter(Player* _pPlayer) = 0;
    //更新
    virtual void Update(Player* _pPlayer) = 0;

    virtual void HandleInput(Player* _pPlayer) = 0;

    //終わるときに発動（アニメーションなど）
    virtual void Exit(Player* _pPlayer) = 0;

    //状態変化
    void Changestate(PlayerState* _nowState, PlayerState* _state);
};