#pragma once
#include "Enemy/Boss_Slime/Boss_Fafrotskies.h"


//�t�@�t���b�L�[�̃X�e�[�g���N���X
class BossState
{
public:
	//�X�V
	 void Update(Fafro* _pFafro) {};
	
	//�X�e�[�g���Ƃ̏���
	 void Process(Fafro* _pFafro) {};

	//�X�e�[�g�̕ύX
	void ChangeState(BossState* prev, BossState* next);
};

class BossSpawn : public BossState {
public:
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossMove : public BossState{
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossWait : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossAttack : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossDamaged : public BossState{
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};

class BossDeath : public BossState {
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};