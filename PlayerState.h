#pragma once

class Player;

//プレイヤーステートの基底クラス
class PlayerState{
public:
    //変更されたときに発動
    virtual void Enter(Player* player) = 0;
    //更新
    virtual void Update(Player* player) = 0;
    //終わるときに発動（アニメーションなど）
    virtual void Exit(Player* player) = 0;

    //状態変化
    void Changestate(PlayerState* _nowState, PlayerState* _state);
};