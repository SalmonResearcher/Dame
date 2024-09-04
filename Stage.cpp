#include "Stage.h"
#include "SkySphere.h"
#include "Engine/Model.h"

namespace
{
    SkySphere* pSky_;
}
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_ = Model::Load("newStage3.fbx");
    assert(hModel_ >= 0);

    pSky_ = Instantiate<SkySphere>(this);
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void Stage::Release()
{
}