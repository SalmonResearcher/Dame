#pragma once
#include "Player.h"

class StateManager
{
public:
	void Update(Player* _p);

	void Enter(Player* _p);

	void HandleInput(Player* _p);
};

