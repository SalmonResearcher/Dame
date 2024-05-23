#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Sprite.h"

#include "Player.h"
#include "JewelBox.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1), hModel_2(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_ = Model::Load("Stage3.fbx");
    assert(hModel_ >= 0);

    hModel_2 = Model::Load("SkySphere.fbx");
    assert(hModel_2 >= 0);

}

//�X�V
void Stage::Update()
{
    transSky_.rotate_.y += 0.2f;
    transSky_.scale_ = { 1.5,1.5,1.5 };
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transStage_);
    Model::Draw(hModel_);
    Model::SetTransform(hModel_2, transSky_);
    Model::Draw(hModel_2);
}

//�J��
void Stage::Release()
{
}