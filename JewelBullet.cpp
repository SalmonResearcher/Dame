#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "TutorialStage.h"

#include "Player.h"
#include "Enemy.h"
#include "JewelBox.h"

//Debug�p
#include "Engine/Debug.h"
#include "Engine/Input.h"


#include <cmath>
#include "Global.h"

namespace {
    const int JEWEL_DEATH_TIME = 180;       //��Βe��������t���[��
    const float JEWEL_ROTATE_SPEED = 8.0f;  //��Βe�̉�]���x
    const float JEWEL_WALL_DEATH = 1.5f;    //��Βe���ǂɂԂ���������

    const float JEWEL_SHOOT_SPEED = 0.8f;   //��Βe�̑��x
    const float JEWEL_GRAUND_OFFSET = 0.5f; //��Βe�̐������̒�グ���鍂��

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

    hStage_ = SetStageHandle();

}

//�X�V
void JewelBullet::Update()
{
    transform_.rotate_.z += JEWEL_ROTATE_SPEED;

    //�ǂɂԂ������������
    RayCastData front;
    front.start = { transform_.position_ };   //���C�̔��ˈʒu
    front.dir = XMFLOAT3(0, 0, 1);       //���C�̕���
    Model::RayCast(hStage_, &front); //���C�𔭎�
   
    Shoot();


    if (front.dist <JEWEL_WALL_DEATH) {
        KillMe();
    }

    if (deleteTime_ >= JEWEL_DEATH_TIME)
    {
        KillMe();
        killCount_ = 0;
    }
    deleteTime_++;    
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

    bulletPos_.x += moveFloat.x * JEWEL_SHOOT_SPEED;
    bulletPos_.z += moveFloat.z * JEWEL_SHOOT_SPEED;

    transform_.position_ = bulletPos_;
    transform_.position_.y = bulletPos_.y + JEWEL_GRAUND_OFFSET;
}

void JewelBullet::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Enemy")
    {
        Enemy* pEnemy = (Enemy*)pTarget;
        pEnemy->JewelDeath();
    }

    if (pTarget->GetObjectName() == "JewelBox")
    {
        score_ = CalculateScore(killCount_);
        ((JewelBox*)FindObject("JewelBox"))->AddScore(score_);
        if (score_ != Global::GetJewelScore())
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
    int baseScore = Global::GetJewelScore(); // �Œ�̓_
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

int JewelBullet::SetStageHandle()
{
    if ((FindObject("Stage")) != nullptr)
    {
        return ((Stage*)FindObject("Stage"))->GetModelHandle();
    }
    else if ((FindObject("TutorialStage")) != nullptr)
    {
        return ((TutorialStage*)FindObject("TutorialStage"))->GetModelHandle();
    }
    return -1;
}