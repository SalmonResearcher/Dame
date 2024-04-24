#pragma once
#include "../BossSlime/Boss_Fafrotskies.h"


//ボスの状態の基底クラス
class BossState
{
public:
	//更新
	virtual void Update(Fafro* _pFafro) {};
	
	//ステートごとの処理
	virtual void Process(Fafro* _pFafro) {};

	//ステートの変更
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