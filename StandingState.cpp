#include "StandingState.h"

#include "Player.h"
#include "Engine/Input.h"


//�X�V
void StandingState::Update(Player* _p)
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		_p->
	}
	//HandleInput(_p);

	////�v���C���[�ƃX�e�[�W�̐ڒn
	//RayCastData grounding; {
	//	grounding.start = { _p->GetPosition().x, 0, _p->GetPosition().z };
	//	grounding.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	//	Model::RayCast(_p->GetPlayerStage(), &grounding); //���C�𔭎�

	//}
	//if (grounding.dist < _p->PLAYER_SIZE.y / 2)
	//{

	//}
	
}

void StandingState::Enter(Player* _p)
{
}

void StandingState::HandleInput(Player* _p)
{
}
