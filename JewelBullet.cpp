#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"
#include "JewelBox.h"

//Debug�p
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>


//�R���X�g���N�^
JewelBullet::JewelBullet(GameObject* parent)
    :GameObject(parent, "JewelBullet"), hModel_(-1), deleteTime_(0)
{

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(collision);
}

//�f�X�g���N�^
JewelBullet::~JewelBullet()
{
}

//������
void JewelBullet::Initialize()
{
    //Jewel.fbx�̃��f�����W������Ă��Ďg�����ɂȂ�Ȃ�
    hModel_ = Model::Load("JewelBullet.fbx");
    assert(hModel_ >= 0);

    hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

}

//�X�V
void JewelBullet::Update()
{
    tJBullet_.rotate_.z += 8;
    RayCastData data;
    data.start = { tJBullet_.position_.x,0,tJBullet_.position_.z };   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hStage_, &data); //���C�𔭎�

    RayCastData front;
    front.start = { tJBullet_.position_ };   //���C�̔��ˈʒu
    front.dir = XMFLOAT3(0, 0, 1);       //���C�̕���
    Model::RayCast(hStage_, &front); //���C�𔭎�


   
    Shoot();

    tJBullet_.position_.y = -data.dist + 0.5f;
    if (front.dist <1.0f) {
        KillMe();
    }

    if (deleteTime_ >= 180)
    {
        KillMe();
    }

    transform_ = tJBullet_;
    deleteTime_++;
}

//�`��
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, tJBullet_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}

void JewelBullet::Shoot()
{
    XMFLOAT3 moveFloat;
    XMStoreFloat3(&moveFloat, playerForwardVec_);

    initPos.x += moveFloat.x * 0.8;
    initPos.z += moveFloat.z * 0.8;

    tJBullet_.position_ = initPos;

}

void JewelBullet::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Enemy")
    {
        pTarget->GetParent();
        killCount_++;
    }

    if (pTarget->GetObjectName() == "JewelBox")
    {
        score_ = CalculateScore(killCount_);
        ((JewelBox*)FindObject("JewelBox"))->AddScore(score_);
        KillMe();
    }
}

int JewelBullet::CalculateScore(int killCount)
{
    int baseScore = 200; // �Œ��200�_
    std::vector<int> scores = { 25, 50, 75, 150, 300, 3000 };

    //�|��������1�`4�̎�
    if (killCount >= 1 && killCount < 5) {
        return scores[killCount - 1] + baseScore;
    }
    //�G��|��������5�ȏ�̎�
    else if (killCount >= 5 && killCount < 10) {
        return scores[4] * (killCount - 4) + baseScore; // 6�̎���300*2�A7�̎���300*3�ƂȂ�
    }
    else if (killCount >= 10) {
        return scores[5] * (killCount - 9) + baseScore;
    }
    else {
        return baseScore; // killCount��0�ȉ��̎��͕�΂݂̂̓_
    }
}