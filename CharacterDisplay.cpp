#include "CharacterDisplay.h"
#include "Score.h"
#include "Engine/Debug.h"

#include "Enemy/Enemy.h"
#include "Player.h"
#include "JewelBox.h"
#include "JewelBullet.h"

#include <math.h>


//�R���X�g���N�^
CharacterDisplay::CharacterDisplay(GameObject* parent)
	: GameObject(parent, "CharacterDisplay"),pText_(nullptr)
{
}

//������
void CharacterDisplay::Initialize()
{
	pText_ = new Text;
	pText_->Initialize("score_number.png", 50, 256, 10);
	pScore_ = Instantiate<Score>(this);
}

//�X�V
void CharacterDisplay::Update()
{
}

//�`��
void CharacterDisplay::Draw()
{
	pScore_->Draw(950,15);
}

//�J��
void CharacterDisplay::Release()
{
}