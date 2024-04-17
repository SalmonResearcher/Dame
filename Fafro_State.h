#pragma once
class Fafro_State
{
public:
	virtual void Spawn() = 0;
	virtual void Wait() = 0;
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Damege() = 0;
	virtual void Death() = 0;
	virtual ~Fafro_State() {}

	void ChangeState(Fafro_State* now,Fafro_State* next)
};

