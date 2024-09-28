#include "SkySphere.h"
#include "Player.h"

#include "Engine/Model.h"

//�R���X�g���N�^
SkySphere::SkySphere(GameObject* parent)
    :GameObject(parent, "SkySphere"), hModel_(-1)
{
}

//�f�X�g���N�^
SkySphere::~SkySphere()
{
}

//������
void SkySphere::Initialize()
{
    hModel_ = Model::Load("SkySphere.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = SCALE;
    pPlayer_ = static_cast<Player*>(FindObject("Player"));
}

//�X�V
void SkySphere::Update()
{
    transform_.rotate_.y += ROTATE_SPEED;
    transform_.position_ = pPlayer_->GetPlayerPosition();
}

//�`��
void SkySphere::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//�J��
void SkySphere::Release()
{
}