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
	//現在の状態を更新
	pBossState_->Update(_pFafro);
}

void FafroStateManager::Process(Fafro* _pFafro)
{
}

void FafroStateManager::ChangeState(BossState* change, Fafro* fafro, bool flg)
{
	//制限されていたら変化しない
	if (isRestricted_) {
		return;
	}

	prevState_ = pBossState_;

	//前Fのステートと変えたいステートが同じなければ変移
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
