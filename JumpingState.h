#pragma once
#include "PlayerState.h"
class JumpingState :
    public PlayerState
{
public:
	void Update(Player* _p);

	void Enter(Player* _p);

	void HandleInput(Player* _p);
};

