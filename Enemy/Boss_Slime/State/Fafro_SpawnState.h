#pragma once
#include "Enemy/Boss_Slime/State/Fafro_State.h"
#include "Enemy/Boss_Slime/Boss_Fafrotskies.h"

class Fafro_SpawnState :public Fafro_State
{
public:
	void Update(Fafro* _pFafro) override;
	void Process(Fafro* _pFafro)override;
	void ChangeState(Fafro_State* prev, Fafro_State* next);

};

