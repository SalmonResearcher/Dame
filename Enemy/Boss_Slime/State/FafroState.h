#pragma once
#include "Enemy/Boss_Slime/State/FafroState.h"
#include "Enemy/Boss_Slime/Boss_Fafrotskies.h"

//��ԑJ�ڂ��Ǘ�����
class BossStateManager : public BossState
{
public:
	BossState* pBossState_;
	BossState* prevState_;

	BossSpawn* pSpawn_;
	BossMove* pMove_;
	BossWait* pWait_;
	BossDamaged* pDameged_;
	BossAttack* pAttack_;
	BossDeath* pDeath_;
	bool canChange_;

	BossStateManager();
	~BossStateManager();

	//�X�V
	virtual void Update()
};

