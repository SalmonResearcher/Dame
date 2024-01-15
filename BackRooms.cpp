#include "BackRooms.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

#include "Player.h"

BackRooms::BackRooms(GameObject* parent)
 :GameObject(parent, "BackRooms"), hModel_(-1)
{
}

//�f�X�g���N�^
BackRooms::~BackRooms()
{
}

//������
void BackRooms::Initialize()
{
    hModel_ = Model::Load("BackRooms.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void BackRooms::Update()
{
}

//�`��
void BackRooms::Draw()
{
    Model::SetTransform(hModel_, transBackRooms_);
    Model::Draw(hModel_);
}

//�J��
void BackRooms::Release()
{
}