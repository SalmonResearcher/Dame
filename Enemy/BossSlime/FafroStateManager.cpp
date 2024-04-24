#include "FafroStateManager.h"

FafroStateManager::FafroStateManager()
{
	pSpawn_ = new BossSpawn;
	pWait_ = new BossWait;
	pMove_ = new BossMove;
	pAttack_ = new BossAttack;
	pDameged_ = new BossDamaged;
	pDeath_ = new BossDeath;
	pBossState_ = pSpawn_;
}

FafroStateManager::~FafroStateManager()
{
	delete pSpawn_;
	delete pWait_;
	delete pMove_;
	delete pAttack_;
	delete pDameged_;
	delete pDeath_;
}

void FafroStateManager::Update(Fafro* _pFafro)
{
	//���݂̏�Ԃ��X�V
	pBossState_->Update(_pFafro);
}

void FafroStateManager::Process(Fafro* _pFafro)
{
}

void FafroStateManager::ChangeState(BossState* change, Fafro* fafro, bool flg)
{
	//��������Ă�����ω����Ȃ�
	if (isRestricted_) {
		return;
	}

	prevState_ = pBossState_;

	//�OF�̃X�e�[�g�ƕς������X�e�[�g�������Ȃ���Εψ�
	if (prevState_ != change) {
		prevState_ = change;
		if (flg){
			pBossState_->Process(fafro);
		}
	}
}

void FafroStateManager::ChangeState(BossState* change, Fafro* fafro)
{
	ChangeState(change, fafro, true);
}
