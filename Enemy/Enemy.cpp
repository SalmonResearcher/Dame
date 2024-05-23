#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/Debug.h"
#include "../EnemyAttack.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), startFrame(0), endFrame(100), animeSpeed(1)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
	hModel_ = Model::Load("Slime.fbx");
	assert(hModel_ >= 0);

	tEnemy_.scale_ = { 0.7f ,0.7f,0.7f };

	tEnemy_.position_.x = target_.x;
	tEnemy_.position_.y = target_.y;
	tEnemy_.position_.z = 5;

	SphereCollider* pSpher = new SphereCollider(XMFLOAT3(0,0,0), 1.25f);
	AddCollider(pSpher);

	Model::SetAnimFrame(hModel_, 0, 100, 1);
	states = MOVE;

	EnemyAttack* pEAtk = Instantiate<EnemyAttack>(GetParent());
	pEAtk->SetTime();
}

//�X�V
void Enemy::Update()
{
	XMFLOAT3 bonePosition_ = Model::GetBonePosition(hModel_, "middle");
	//�ǂ������違�U�����邽�߂�
	target_ = ((Player*)FindObject("Player"))->GetPlayerPos();
	//�v���C���[�܂ł̋���
	toPlayerdir = sqrtf(pow((target_.x - tEnemy_.position_.x), 2) + pow((target_.z - tEnemy_.position_.z), 2));

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = { tEnemy_.position_.x,0,tEnemy_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	if (data.hit)
	{
		tEnemy_.position_.y = -data.dist;
	}

	switch (states)
	{
	case MOVE:
		ChasePlayer(target_, 0.2f);

		if (toPlayerdir < 5.0f)
		{
			waitTime = 36;
			states = ATTACK;
		}

		Debug::Log("toPlayerDir = ");
		Debug::Log(toPlayerdir, true);
		break;

	case ATTACK:
		Attack();
		ChasePlayer(target_, 0.0f);

		if (waitTime <= 0 && toPlayerdir >= 4.0f)
		{
			states = MOVE;
			waitTime = 0;
		}
		waitTime--;
		break;

	case DEATH:
		if (waitTime <= 0)
		{
			KillMe();
		}
		waitTime--;
		break;

	default:
		states = DEATH;
		break;

	}
	//tEnemy_.position_.z += 0.03f;

	if (curState != states)
	{
		ChangeAnime(states);
		curState = states;
	}
	
	tEnemy_.position_ ;

	transform_.position_ = tEnemy_.position_;

}

//�`��
void Enemy::Draw()
{
	Model::SetTransform(hModel_, tEnemy_);
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
		waitTime = 20;
		Death();
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&tEnemy_.position_);

	//�^�[�Q�b�g�Ɍ������ĐL�тĂ���x�N�g��
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	//���K��
	direction_ = XMVector3Normalize(direction_);

	//direction_�̕�����speed�Ԃ񓮂�
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&tEnemy_.position_, newVecPos_);

	// �G����v���C���[�Ɍ����������x�N�g������p�x�����߂�
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); // atan2(z, x)���g�p���Ċp�x���v�Z

	// �p�x��x���@�ɕϊ�����i���W�A������x�ɕϊ��j
	angle = XMConvertToDegrees(angle);

	tEnemy_.rotate_.y = angle;
}

void Enemy::Attack()
{

}

void Enemy::Death()
{
		states = DEATH;
		isDead = true;
}

void Enemy::ChangeAnime(STATE state)
{
	switch (state)
	{
	case MOVE:
		Model::SetAnimFrame(hModel_, 0, 100, 1);
		break;

	case ATTACK:
		Model::SetAnimFrame(hModel_, 110, 140, 0.8);
		break;

	case DEATH:
		Model::SetAnimFrame(hModel_, 150, 175, 1);
		break;

	default:
		states = DEATH;
		break;
	}
}
