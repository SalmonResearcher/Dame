#pragma once
#include "../State/BossState.h"
#include "Boss_Fafrotskies.h"

//ó‘Ô‘JˆÚ‚ğŠÇ—‚·‚é
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

	//XV
	virtual void Update()
};

