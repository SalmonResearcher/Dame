#include "StandingState.h"

#include "Player.h"
#include "Engine/Input.h"


//更新
void StandingState::Update(Player* _p)
{
	HandleInput(_p);

	RayCastData grounding;
	grounding.start = { _p->GetPosition().x, 0, _p->GetPosition().z };
	grounding.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hGroundModel, &grounding); //レイを発射

}

void StandingState::Enter(Player* _p)
{
}

void StandingState::HandleInput(Player* _p)
{
}
