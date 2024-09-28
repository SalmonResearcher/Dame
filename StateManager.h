#pragma once
#include "StateBase.h"
#include <string>
#include <map>

class GameObject;

class StateManager
{
private:
	//ó‘Ô‚ğ•¶š—ñ‚ÅŠÇ—
	std::map<std::string, StateBase*>statesMap_;
	StateBase* currentState_;
	GameObject* pParent_;

public:
	StateManager(GameObject* parent);
	~StateManager();

	void Update();
	void ChangeState(const std::string& stateName);
	StateBase* AddState(const std::string& stateName, StateBase* state);
	GameObject* GetGameObject() { return pParent_; }
};

