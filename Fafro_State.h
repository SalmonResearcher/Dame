#pragma once

class Fafro;

//�t�@�t���b�L�[�̃X�e�[�g���N���X
class Fafro_State
{
public:
	//�X�V
	void Update(Fafro* _pFafro) {};
	
	//�X�e�[�g���Ƃ̏���
	void Process(Fafro* _pFafro) {};

	//�X�e�[�g�̕ύX
	void ChangeState(Fafro_State* prev, Fafro_State* next);
};

