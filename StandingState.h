#pragma once
#include "PlayerState.h"
#include "PlayerStateManager.h"

//—§‚¿ó‘Ô
class StandingState : public PlayerState
{
public:
	void Update(Player* _p);

	void Enter(Player* _p);

	void HandleInput(Player* _p);
};

