#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include "Jewel.h"
#include "JewelBullet.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "EnemyAttack.h"
#include "EnemySpawn.h"
#include "Engine/Audio.h"
#include "Engine/VFX.h"
#include "StateManager.h"
#include "EnemyState.h"

#include <algorithm> // std::max���g��

namespace 
{
	XMFLOAT3 ColliderPosition = { 0.0f,0.0f,0.0f };
	float ColliderScale = 1.25f;

	XMFLOAT3 enemyScale = { 1.0f,1.0f,1.0f };
	float attackDistance = 1.5f;	//���̒l�����܂ŋ߂Â��ƍU���Ɉڍs
	float moveDistance = 2.0f;		//���̒l�𒴂��鋗���܂ŉ�������ƈړ�


	float moveY = 0.0f;
	float speed_ = 0.0f;

	float moveSpeed = 0.12f;
	float attackSpeed = 0.0f;


	int collisionCreateTime = 42;	//�U��������܂ł̎���
	int collisionTime = 3;		//����̎����t���[��

	int attackWaitTime = 90;
	int deadWaitTime = 60;

	int deathSoundTime = 14;

	float falloff = 45.0f;		//�����ŏ��ɂȂ�܂ł̋���

	EnemySpawn* pEnemySpawn;

	float soundVolume = 0.18f;	//�ő剹��
	float maxSoundDistance = 5.0f;	//�ő剹�ʋ���
	float min = 0.8f;			//���̍Œ�s�b�`
	float max = 1.2f;			//���̍ő�s�b�`

	float deathPitch;			//�|���ꂽ���̃s�b�`
	float hitPitch;				//�U�����󂯂��Ƃ��s�b�`
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hStage_(-1), pPlayer_(nullptr), counted_(false)
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

	hDeathSound_ = Audio::Load("SE/SlimeDeath.WAV", false, 1);
	assert(hDeathSound_ >= 0);

	hHitSound_ = Audio::Load("SE/Attack2.wav", false, 1);
	assert(hHitSound_ >= 0);

	transform_.scale_ = { enemyScale };

	pEnemySpawn = static_cast<EnemySpawn*>(FindObject("EnemySpawn"));
	transform_.position_ = pEnemySpawn->GetSpawnPoint();

	pSpher_ = new SphereCollider(ColliderPosition, ColliderScale);
	AddCollider(pSpher_);


	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	pPlayer_ = static_cast<Player*>(FindObject("Player"));

	pStateManager_ = new StateManager(this);

	pStateManager_->AddState("EnemyWalkState", new EnemyWalkState(pStateManager_));
	pStateManager_->AddState("EnemyAttackState", new EnemyAttackState(pStateManager_));
	pStateManager_->AddState("EnemyDeadState", new EnemyDeadState(pStateManager_));

	//�������
	pStateManager_->ChangeState("EnemyWalkState");
}

//�X�V
void Enemy::Update()
{
	deathPitch = GenerateRandomFloat(min,max);
	hitPitch = GenerateRandomFloat(min, max);


	//�ǂ������違�U�����邽�߂̊֐�
	//target_ = pPlayer->GetPlayerPosition();

	//�v���C���[�܂ł̋���
	toPlayerdir_ = sqrtf(pow((target_.x - transform_.position_.x), 2) + pow((target_.z - transform_.position_.z), 2));

	volume_ = SoundDistance(toPlayerdir_, falloff);

	// �X�e�[�g�}�l�[�W���[�̍X�V
	pStateManager_->Update();


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	if (toPlayerdir_ < moveDistance)
	{
		isNearPlayer_ = true;
	}
	else if(waitTime_ <= 0 && toPlayerdir_ >= attackDistance)
	{
		isNearPlayer_ = false;
	}

	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}

	else
	{
		KillMe();
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

void Enemy::Walk()
{
	//�ǂ������違�U�����邽�߂̊֐�
	target_ = pPlayer_->GetPlayerPosition();
	speed_ = moveSpeed;
	ChasePlayer(target_, speed_);
}

void Enemy::Attack() 
{
	speed_ = attackSpeed;
	ChasePlayer(target_, speed_);

	if ((attackWaitTime - collisionCreateTime) == waitTime_) {
		AttackCollision();
	}


	if (waitTime_ <= 0)
	{
		waitTime_ = 0;
		isAttackEnd_ = true;
		pStateManager_->ChangeState("EnemyWalkState");
		return;
	}
	waitTime_--;
}

void Enemy::Dead()
{

	if (waitTime_ == deathSoundTime)
	{
		Audio::Play(hDeathSound_, true, deathPitch, volume_);
		CreateVFX(DEATH);
	}

	if (waitTime_ < 0)
	{
		((Player*)FindObject("Player"))->KillCountUp();
		Jewel* pJewel = InstantiateFront<Jewel>(GetParent());
		pJewel->SetPosition(transform_.position_);
		KillMe();
	}
	waitTime_--;

}

void Enemy::AttackCollision() 
{
	EnemyAttack* pEAttack = Instantiate<EnemyAttack>(GetParent());
	pEAttack->SetAttackPosition(transform_.position_);
	pEAttack->SetTime(collisionTime);
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack" && !isDead_)
	{
		Audio::Play(hHitSound_, true, hitPitch, volume_);

		CreateVFX(HIT);
		isDead_ = true;
	}
	if (pTarget->GetObjectName() == "JewelBullet" && !counted_)
	{
		Audio::Play(hHitSound_, true, hitPitch, volume_);

		CreateVFX(JEWEL);
		JewelBullet* pBullet = (JewelBullet*)pTarget;
		pBullet->SetKillCount(1);
		counted_ = true;
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{

	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&transform_.position_);

	//�^�[�Q�b�g�Ɍ������ĐL�тĂ���x�N�g��
	direction_ = XMVectorSubtract(vTarget_, vPosition_);
	direction_ = XMVector3Normalize(direction_);

	//direction_�̕�����speed�Ԃ񓮂�
	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transform_.position_, newVecPos_);

	// �G����v���C���[�Ɍ����������x�N�g������p�x�����߂�
	float angle = atan2(XMVectorGetX(direction_), XMVectorGetZ(direction_)); 

	// �p�x��x���@�ɕϊ�����i���W�A������x�ɕϊ��j
	angle = XMConvertToDegrees(angle);

	transform_.rotate_.y = angle;
}

void Enemy::JewelDeath()
{
	waitTime_ = deadWaitTime;
	isDead_ = true;
}


float Enemy::SoundDistance(float distance, float falloff)
{
	float volume = soundVolume - (distance - maxSoundDistance) / falloff;
	return max(0.0f, volume);
}

float Enemy::GenerateRandomFloat(float min, float max)
{
	// 0.0����1.0�͈̗̔͂����𐶐�
	float random = static_cast<float>(rand()) / RAND_MAX; 

	// min����max�͈̔͂ɃX�P�[�����O
	return min + random * (max - min); 
}

void Enemy::CreateVFX(STATEVFX svfx) 
{
	switch (svfx) 
	{
	case HIT:
		vfx_.textureFileName = "paticleAssets/flashA_W.png";
		vfx_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + HIT_EFFECT_OFFSET_Y, transform_.position_.z);
		vfx_.number = 1;
		vfx_.positionRnd = XMFLOAT3(0, 0, 0);
		vfx_.direction = XMFLOAT3(0, 0, 0);
		vfx_.directionRnd = XMFLOAT3(0, 0, 0);
		vfx_.size = EFFECT_SIZE_LARGE;
		vfx_.scale = EFFECT_SCALE_DEFAULT;
		vfx_.lifeTime = LIFETIME_SHORT;
		vfx_.speed = 0;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = 0;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	case JEWEL:
		vfx_.textureFileName = "paticleAssets/flashA_B.png";
		vfx_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + HIT_EFFECT_OFFSET_Y, transform_.position_.z);
		vfx_.number = 1;
		vfx_.positionRnd = XMFLOAT3(0, 0, 0);
		vfx_.direction = XMFLOAT3(0, 0, 0);
		vfx_.directionRnd = XMFLOAT3(0, 0, 0);
		vfx_.size = EFFECT_SIZE_LARGE;
		vfx_.scale = EFFECT_SCALE_DEFAULT;
		vfx_.lifeTime = LIFETIME_SHORT;
		vfx_.speed = 0;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = 0;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	case DEATH:
		vfx_.textureFileName = "paticleAssets/star.png";
		vfx_.position = transform_.position_;
		vfx_.number = 3;
		vfx_.positionRnd = POSITION_RND_DEATH;
		vfx_.direction = XMFLOAT3(0, 1, 0);
		vfx_.directionRnd = DIRECTION_RND_DEATH;
		vfx_.size = EFFECT_SIZE_SMALL;
		vfx_.scale = EFFECT_SCALE_SMALL;
		vfx_.lifeTime = LIFETIME_LONG;
		vfx_.speed = EFFECT_SPEED_DEATH;
		vfx_.spin = EFFECT_SPIN;
		vfx_.gravity = EFFECT_GRAVITY;
		vfx_.delay = 0;
		hEmit_ = VFX::Start(vfx_);
		break;

	default:
		break;
	}
}
void Enemy::DestroyVFX()
{
	stopEmit_ = true;
}

void Enemy::SetAttackTime()
{
	waitTime_ = attackWaitTime;
}

void Enemy::SetDeadTime()
{
	waitTime_ = deadWaitTime;
}