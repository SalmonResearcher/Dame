#pragma once
#include "Engine/Global.h"

class Player;

class PlayerState
{
public:
	//�X�V
	virtual void Update(Player* _p) {};

	//����
	virtual void HandleInput(Player* _p) {};

	//��ԕω������Ƃ�
	virtual void Enter(Player* _p) {};

	//��ԕω�
	void StateChange(PlayerState* _current, PlayerState* _next);
};

