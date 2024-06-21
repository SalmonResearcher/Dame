#pragma once
#include "PlayerState.h"

//ステートたち
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

	//ステート変更（trueで変更）
	void ChangeState(PlayerState* _change, Player* _pPlayer, bool _flg);

	void ChangeState(PlayerState* _change, Player* _pPlayer);




};

