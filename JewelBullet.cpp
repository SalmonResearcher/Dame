#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Player.h"
#include "Enemy/Enemy.h"
#include "JewelBox.h"

//Debug�p
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>
#include "Global.h"

namespace {

    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;
}

//�R���X�g���N�^
JewelBullet::JewelBullet(GameObject* parent)
    :GameObject(parent, "JewelBullet"), hModel_(-1)
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
    transform_.rotate_.z += 8;

    //�ǂɂԂ������������
    RayCastData front;
    front.start = { transform_.position_ };   //���C�̔��ˈʒu
    front.dir = XMFLOAT3(0, 0, 1);       //���C�̕���
    Model::RayCast(hStage_, &front); //���C�𔭎�
   
    Shoot();


    if (front.dist <1.5f) {
        KillMe();
    }

    if (deleteTime_ >= 180)
    {
        KillMe();
        killCount_ = 0;
    }
    deleteTime_++;

    Debug::Log("��΂œG��|������ = ");
    Debug::Log(killCount_, true);
    
}

//�`��
void JewelBullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void JewelBullet::Release()
{
}

void JewelBullet::BulletDirection(XMVECTOR _dir)
{
    playerForwardVec_ = _dir;
}

void JewelBullet::BulletPosition(XMFLOAT3 _pos)
{
    playerPos_ = _pos;
    // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
    XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
    XMStoreFloat3(&bulletPos_, bulletInitPos);
};

void JewelBullet::Shoot()
{
    XMFLOAT3 moveFloat;
    XMStoreFloat3(&moveFloat, playerForwardVec_);

    bulletPos_.x += moveFloat.x * 0.8;
    bulletPos_.z += moveFloat.z * 0.8;

    transform_.position_ = bulletPos_;

}

void JewelBullet::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Enemy")
    {
        Enemy* pEnemy = (Enemy*)pTarget;
        pEnemy->Death();
    }

    if (pTarget->GetObjectName() == "JewelBox")
    {
        score_ = CalculateScore(killCount_);
        ((JewelBox*)FindObject("JewelBox"))->AddScore(score_);
        if (score_ != 200)
        {
            Global::AddJewelKill(score_);
        }
        Global::AddJewel(1);
        killCount_ = 0;
        KillMe();
    }
}

int JewelBullet::CalculateScore(int killCount)
{
    int baseScore = 200; // �Œ��200�_
    int scores[] = {25, 50, 75, 150, 300, 1500};

    //�|��������1�`4�̎�
    if (killCount >= 1 && killCount < 5) {
        return scores[killCount - 1] + baseScore;
    }
    //�G��|��������5�ȏ�̎�
    else if (killCount >= 5 && killCount < 10) {
        return scores[4] * (killCount - 4) + baseScore; // 6�̎���300*2�A7�̎���300*3�ƂȂ�
    }
    //10�ȏ�1500*kill-8
    else if (killCount >= 10) {
        return scores[5] * (killCount - 8) + baseScore;
    }
    else {
        return baseScore; // killCount��0�ȉ��̎��͕�΂݂̂̓_
    }
}

void JewelBullet::SetKillCount(int count)
{
    killCount_ += count;
}
