

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
	bool canChange_;

	BossStateManager();
	~BossStateManager();

	//�X�V
	virtual void Update()
};