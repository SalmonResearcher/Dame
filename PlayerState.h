#pragma once
#include "Engine/GameObject.h"
class Player;

class PlayerState:public GameObject
{
public:
    virtual ~PlayerState() {}
    virtual void Enter(Player* player) = 0;
    virtual void Update(Player* player) = 0;
    virtual void Exit(Player* player) = 0;
};