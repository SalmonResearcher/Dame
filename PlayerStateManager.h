//#pragma once
//#include "PlayerState.h"
//
//#include "StandingState.h"
//#include "WalkingState.h"
//#include "JumpingState.h"
//
//class Player;
//class StandingState;
//class WalkingState;
//class JumpingState;
//
//
//class PlayerStateManager
//{
//public:
//	//現在と過去のステート
//	PlayerState* nowState_;
//	PlayerState* prevState_;
//
//	//ステート一覧
//	PlayerState* pPlayerState_;
//	StandingState* pStand_;
//	WalkingState* pWalk_;
//	JumpingState* pJump_;
//
//	//コンストラクタ
//	PlayerStateManager();
//	~PlayerStateManager();
//
//	//更新
//	virtual void Update(Player* _p);
//
//	//入力
//	virtual void HandleInput(Player* _p);
//
//	//スタートした時に実行
//	virtual void Execute(Player* _p);
//
//	/// <summary>
//	/// 状態を遷移します
//	/// </summary>
//	/// <param name="pChange_">遷移したい状態</param>
//	/// <param name="_p">対象</param>
//	/// <param name="execute_">実行するか</param>
//	void ChangeState(PlayerState* pChange_, Player* _p, bool execute_);
//
//	/// <summary>
//	/// 状態を遷移します
//	/// </summary>
//	/// <param name="pChange_">遷移したい状態</param>
//	/// <param name="p_">対象</param>
//	void ChangeState(PlayerState* pChange_, Player* p_);
//
//};
//
