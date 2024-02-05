#include "StandingState.h"

#include "Player.h"
#include "Engine/Input.h"


//XV
void StandingState::Update(Player* _p)
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//_p->GetState()->ChangeState(_p->GetState()->pJump,_p,false );
	}

	//if(_p->GetState()->pState_ == )
}

void StandingState::Enter(Player* _p)
{
}

void StandingState::HandleInput(Player* _p)
{
}
