#pragma once
#include "Enemy/Boss_Slime/Boss_Fafrotskies.h"


//ファフロッキーのステート基底クラス
class BossState
{
public:
	//更新
	 void Update(Fafro* _pFafro) {};
	
	//ステートごとの処理
	 void Process(Fafro* _pFafro) {};

	//ステートの変更
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