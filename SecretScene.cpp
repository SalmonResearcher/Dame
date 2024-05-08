#include "SecretScene.h"
#include "Engine/Model.h"
#include "Player.h"

//�R���X�g���N�^
SecretScene::SecretScene(GameObject* parent)
	: GameObject(parent, "SecretScene") , hModel_(-1)
{
}

//������
void SecretScene::Initialize()
{
	hModel_ = Model::Load("LevelEntrance.fbx");
	assert(hModel_ >= 0);

	Instantiate<Player>(this);
}

//�X�V
void SecretScene::Update()
{
}

//�`��
void SecretScene::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

//�J��
void SecretScene::Release()
{
}
