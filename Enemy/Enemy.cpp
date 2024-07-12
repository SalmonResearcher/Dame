#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Jewel.h"
#include "../JewelBullet.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../EnemyAttack.h"
#include "../EnemySpawn.h"

namespace 
{
	XMFLOAT3 CollisionPosition = { 0.0f,0.0f,0.0f };
	float CollisionScale = 1.25f;

	XMFLOAT3 enemyScale = { 1.0f,1.0f,1.0f };
	float attackDistance = 1.5f;
	float moveDistance = 2.0f;

	struct AnimFrame
	{
		int startFrame;
		int endFrame;
		float speed;
	};
	AnimFrame anim1;
	AnimFrame anim2;
	AnimFrame anim3;

	float moveY = 0.0f;
	float speed_ = 0.8f;

	int collisionCreateTime = 42;	//�U��������܂ł̎���
	int collisionTime = 3;		//����̎����t���[��

	int attackWaitTime = 90;
	int deathWaitTime = 60;
	EnemySpawn* pEnemySpawn;


}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), pPlayer(nullptr), counted(false)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
	hModel_ = Model::Load("Slime_V2.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { enemyScale };

	pEnemySpawn = static_cast<EnemySpawn*>(FindObject("EnemySpawn"));
	transform_.position_ = pEnemySpawn->GetSpawnPoint();

	pSpher = new SphereCollider(XMFLOAT3(0,0,0), 1.25f);
	AddCollider(pSpher);


	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	pPlayer = static_cast<Player*>(FindObject("Player"));
	
	{
		anim1.startFrame = 0;
		anim1.endFrame = 100;
		anim1.speed = 1;

		anim2.startFrame = 110;
		anim2.endFrame = 200;
		anim2.speed = 1;

		anim3.startFrame = 210;
		anim3.endFrame = 400;
		anim3.speed = 1;
	}

	states = MOVE;
	ChangeAnime(states);
}

//�X�V
void Enemy::Update()
{
	//�ǂ������違�U�����邽�߂�
	target_ = pPlayer->GetPlayerPosition();
	//�v���C���[�܂ł̋���
	toPlayerdir = sqrtf(pow((target_.x - transform_.position_.x), 2) + pow((target_.z - transform_.position_.z), 2));


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�



	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}

	switch (states)
	{
	case MOVE:
		speed_ = 0.1f;
		ChasePlayer(target_, speed_);

		if (toPlayerdir < moveDistance)
		{
			waitTime_ = attackWaitTime;
			states = ATTACK;
		}

		break;

	case ATTACK:
		speed_ = 0.0f;
		ChasePlayer(target_, speed_);

		if ((attackWaitTime - collisionCreateTime) == waitTime_) {
			Attack();
		}


		if (waitTime_ <= 0 && toPlayerdir >= attackDistance)
		{
			states = MOVE;
			waitTime_ = 0;
		}
		waitTime_--;
		break;

	case DEATH:
		if (waitTime_ < 0)
		{
			((Player*)FindObject("Player"))->KillCountUp();
			Jewel* pJewel = InstantiateFront<Jewel>(GetParent());
			pJewel->SetPosition(transform_.position_);
			KillMe();
		}
		waitTime_--;
		break;

	default:
		states = DEATH;
		break;

	}

	if (curState != states)
	{
		ChangeAnime(states);
		curState = states;
	}
}

//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

//�J��
void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack" && !isDead)
	{
		Death();
	}
	if (pTarget->GetObjectName() == "JewelBullet" && !counted)
	{
		JewelBullet* pBullet = (JewelBullet*)pTarget;
		pBullet->SetKillCount(1);
		counted = true;
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&transform_.position_);

	//�^�[�Q�b�g�Ɍ������ĐL�тĂ���x�N�g��
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	//���K��
	direction_ = XMVector3Normalize(direction_);

	//direction_�̕�����speed�Ԃ񓮂�
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transform_.position_, newVecPos_);

	// �G����v���C���[�Ɍ����������x�N�g������p�x�����߂�
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); // atan2(z, x)���g�p���Ċp�x���v�Z

	// �p�x��x���@�ɕϊ�����i���W�A������x�ɕϊ��j
	angle = XMConvertToDegrees(angle);

	transform_.rotate_.y = angle;
}


void Enemy::Attack() 
{
	EnemyAttack* pEAttack = Instantiate<EnemyAttack>(GetParent());
	pEAttack->SetAttackPosition(transform_.position_);
	pEAttack->SetTime(collisionTime);
}

void Enemy::Death()
{
	states = DEATH;
	waitTime_ = deathWaitTime;
	isDead = true;
}

void Enemy::JewelDeath()
{
	states = DEATH;
	waitTime_ = deathWaitTime;
	isDead = true;

}

void Enemy::ChangeAnime(STATE state)
{
	switch (state)
	{
	case MOVE:
		Model::SetAnimFrame(hModel_,anim1.startFrame,anim1.endFrame,anim1.speed);
		break;

	case ATTACK:
		Model::SetAnimFrame(hModel_,anim2.startFrame,anim2.endFrame,anim2.speed);
		break;

	case DEATH:
		Model::SetAnimFrame(hModel_,anim3.startFrame,anim3.endFrame,anim3.speed);
		break;

	default:
		states = DEATH;
		break;
	}
}
