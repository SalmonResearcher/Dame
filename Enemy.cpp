#include "Enemy.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),hStage_(-1),isJumping(false)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);
	transEnemy_.position_.x = target_.x;
	transEnemy_.position_.y = target_.y;
	transEnemy_.position_.z = target_.z;
}

//�X�V
void Enemy::Update()
{
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = { transEnemy_.position_.x,0,transEnemy_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	RayCastData play;
	play.start = { transEnemy_.position_.x,transEnemy_.position_.y + 0.3f,transEnemy_.position_.z };   //���C�̔��ˈʒu
	play.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &play); //���C�𔭎�

	if (data.hit)
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping)
		{
			isJumping = true;
			moveY += 0.2f;
		}

		else if (isJumping)
		{
			//���R����
			moveY -= 0.01;

			if (moveY <= -0.25f)
			{
				moveY = -0.25f;
			}
		}

		if (play.dist <= 0.25 && isJumping)
		{
			moveY = 0.0f;
			isJumping = false;
		}

		if (!isJumping)
		{
			transEnemy_.position_.y = -data.dist;
		}

		transEnemy_.position_.y += moveY;
	}


}

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transEnemy_);
    Model::Draw(hModel_);

}

//�J��
void Enemy::Release()
{
}