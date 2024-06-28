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
//	//���݂Ɖߋ��̃X�e�[�g
//	PlayerState* nowState_;
//	PlayerState* prevState_;
//
//	//�X�e�[�g�ꗗ
//	PlayerState* pPlayerState_;
//	StandingState* pStand_;
//	WalkingState* pWalk_;
//	JumpingState* pJump_;
//
//	//�R���X�g���N�^
//	PlayerStateManager();
//	~PlayerStateManager();
//
//	//�X�V
//	virtual void Update(Player* _p);
//
//	//����
//	virtual void HandleInput(Player* _p);
//
//	//�X�^�[�g�������Ɏ��s
//	virtual void Execute(Player* _p);
//
//	/// <summary>
//	/// ��Ԃ�J�ڂ��܂�
//	/// </summary>
//	/// <param name="pChange_">�J�ڂ��������</param>
//	/// <param name="_p">�Ώ�</param>
//	/// <param name="execute_">���s���邩</param>
//	void ChangeState(PlayerState* pChange_, Player* _p, bool execute_);
//
//	/// <summary>
//	/// ��Ԃ�J�ڂ��܂�
//	/// </summary>
//	/// <param name="pChange_">�J�ڂ��������</param>
//	/// <param name="p_">�Ώ�</param>
//	void ChangeState(PlayerState* pChange_, Player* p_);
//
//};
//
