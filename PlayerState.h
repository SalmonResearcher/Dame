#pragma once
#include "Engine/Global.h"

class Player;

class PlayerState
{
public:
	//XV
	virtual void Update(Player* _p) {};

	//“ü—Í
	virtual void HandleInput(Player* _p) {};

	//ó‘Ô•Ï‰»‚µ‚½‚Æ‚«
	virtual void Enter(Player* _p) {};

	//ó‘Ô•Ï‰»
	void StateChange(PlayerState* _current, PlayerState* _next);
};

