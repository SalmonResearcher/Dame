#include "../State/BossState.h"
#include "Boss_Fafrotskies.h"

//��ԑJ�ڂ��Ǘ�����
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

	//��ԑJ�ڂ̋����~��Ă邩���f
	bool isRestricted_;

	FafroStateManager();
	~FafroStateManager();

	//�X�V
	virtual void Update(Fafro* _pFafro)override;
	virtual void Process(Fafro* _pFafro)override;
	void ChangeStateRestricted() {isRestricted_ = true; };

	//��ԑJ�ځi�J�ڌ��... true->���s false->���s���Ȃ��j
	void ChangeState(BossState* change, Fafro* fafro, bool flg);
	//��ԑJ�ځi�J�ڌ�Ɏ��s�j
	void ChangeState(BossState* change, Fafro* fafro);
};