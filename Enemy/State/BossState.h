#pragma once
#include "../BossSlime/Boss_Fafrotskies.h"


//�{�X�̏�Ԃ̊��N���X
class BossState
{
public:
	//�X�V
	virtual void Update(Fafro* _pFafro) {};
	
	//�X�e�[�g���Ƃ̏���
	virtual void Process(Fafro* _pFafro) {};

	//�X�e�[�g�̕ύX
	void ChangeState(BossState* prev, BossState* next);
};

class BossSpawn : public BossState {
public:
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossWait : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossMove : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};


class BossAttack : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossDamaged : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossDeath : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};