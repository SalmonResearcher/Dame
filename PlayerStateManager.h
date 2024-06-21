#pragma once
#include "PlayerState.h"

//�X�e�[�g����
#include "IdleState.h"
#include "MovingState.h"
#include "JumpingState.h"
#include "AttackingState.h"



class PlayerStateManager : public PlayerState
{
public:
	PlayerState* playerState_;
	PlayerState* prevState_;

	IdleState* pIdle_;
	MovingState* pMoving_;
	JumpingState* pJumping_;
	AttackingState* pAttacking_;

	bool stopChange;

public:
	PlayerStateManager();
	~PlayerStateManager();

	virtual void Update(Player* _pPlayer)override;

	virtual void HandleInput(Player* _pPlayer)override;

	virtual void Enter(Player* _pPlayer)override;

	void StopChangeState() { stopChange = true; };

	//�X�e�[�g�ύX�itrue�ŕύX�j
	void ChangeState(PlayerState* _change, Player* _pPlayer, bool _flg);

	void ChangeState(PlayerState* _change, Player* _pPlayer);




};

