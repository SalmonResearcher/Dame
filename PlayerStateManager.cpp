#include "PlayerStateManager.h"

PlayerStateManager::PlayerStateManager(){
	pIdle_ = new IdleState;
	pMoving_ = new MovingState;
	pJumping_ = new JumpingState;
	pAttacking_ = new AttackingState;
}

PlayerStateManager::~PlayerStateManager()
{
	delete pIdle_;
	delete pMoving_;
	delete pJumping_;
	delete pAttacking_;
}

void PlayerStateManager::Update(Player* _pPlayer) {
	playerState_->Update(_pPlayer);
}

void PlayerStateManager::HandleInput()