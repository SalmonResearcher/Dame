#pragma once
class StateManager
{
public:
	void Update(Player* _p);

	void Enter(Player* _p);

	void HandleInput(Player* _p);
};

