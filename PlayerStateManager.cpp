//#include "PlayerStateManager.h"
//
//PlayerStateManager::PlayerStateManager()
//{
//	pStand_ = new StandingState;
//	pWalk_ = new WalkingState;
//	pJump_ = new JumpingState;
//
//	//立ち状態からスタート
//	pPlayerState_ = new StandingState;
//}
//
//PlayerStateManager::~PlayerStateManager()
//{
//	delete pStand_;
//	delete pWalk_;
//	delete pJump_;
//}
//
//void PlayerStateManager::Update(Player* _p)
//{
//	pPlayerState_->Update(_p);
//}
//
//void PlayerStateManager::HandleInput(Player* _p) 
//{
//}
//
//void PlayerStateManager::Execute(Player* _p) 
//{
//	pPlayerState_->Enter(_p); 
//}
//
//void PlayerStateManager::ChangeState(PlayerState* _pChange, Player* _p, bool execute_) 
//{
//	prevState_ = nowState_;
//	if (prevState_ != _pChange)
//	{
//		nowState_ = _pChange;
//		if (execute_)
//		{
//			pPlayerState_->Enter(_p);
//		}
//	}
//};
//
//void PlayerStateManager::ChangeState(PlayerState* _pChange, Player* _p)
//{
//	ChangeState(_pChange, _p, true);
//};
