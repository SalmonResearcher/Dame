#include "../State/BossState.h"
#include "Boss_Fafrotskies.h"

//ó‘Ô‘JˆÚ‚ğŠÇ—‚·‚é
class FafroStateManager : public BossState
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

	//ó‘Ô‘JˆÚ‚Ì‹–‰Â‚ª~‚è‚Ä‚é‚©”»’f
	bool isRestricted_;

	FafroStateManager();
	~FafroStateManager();

	//XV
	virtual void Update(Fafro* _pFafro)override;
	virtual void Process(Fafro* _pFafro)override;
	void ChangeStateRestricted() {isRestricted_ = true; };

	//ó‘Ô‘JˆÚi‘JˆÚŒã‚É... true->Às false->Às‚µ‚È‚¢j
	void ChangeState(BossState* change, Fafro* fafro, bool flg);
	//ó‘Ô‘JˆÚi‘JˆÚŒã‚ÉÀsj
	void ChangeState(BossState* change, Fafro* fafro);
};