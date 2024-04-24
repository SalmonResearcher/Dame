#pragma once

class BossSpawn : public BossState {
public:
	void Update(Fafro* _pFafro);
	void Process(Fafro* _pFafro);
};