#pragma once

class Fafro;

//�t�@�t���b�L�[�̃X�e�[�g���N���X
class Fafro_State
{
public:
	//�X�V
	virtual void Update(Fafro* _pFafro) {};
	
	//�X�e�[�g���Ƃ̏���
	virtual void Process(Fafro* _pfafro) {};

	//�X�e�[�g�̕ύX�inow or prev�Ŗ����Ă�j
	void ChangeState(Fafro_State* now, Fafro_State* next);
};

