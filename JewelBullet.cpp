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


    if (front.dist <JEWEL_WALL_DEATH) 
    {
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

void JewelBullet::BulletPosition(float x, float y, float z)
{
    XMFLOAT3 position{ x, y, z };
    BulletPosition(position);
}

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

    // �|��������1����4�͈̔͂̏ꍇ
    if (killCount >= 1 && killCount < SCORE_BRACKET_THRESHOLD1) 
    {
        return SCORE_BRACKETS[killCount - 1] + baseScore;
    }
    // �|��������5����9�͈̔͂̏ꍇ
    else if (killCount >= SCORE_BRACKET_THRESHOLD1 && killCount < SCORE_BRACKET_THRESHOLD2)
    {
        return SCORE_BRACKETS[SCORE_BRACKET_THRESHOLD1 - 1] * (killCount - SCORE_BRACKET_THRESHOLD1 + 1) + baseScore;
    }
    // �|��������10�ȏ�̏ꍇ
    else if (killCount >= SCORE_BRACKET_THRESHOLD2) 
    {
        return SCORE_BRACKETS[SCORE_BRACKET_COUNT - 1] * (killCount - SCORE_BRACKET_THRESHOLD2 + 1) + baseScore;
    }
    // killCount ��0�ȉ��̏ꍇ
    else 
    {
        return baseScore;
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