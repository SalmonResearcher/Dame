#include "Enemy.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Engine/Input.h"
#include "../Engine/Model.h"
#include "../Engine/SphereCollider.h"
//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),hStage_(-1),isJumping(false),startFrame(0),endFrame(100),animeSpeed(1)
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
	Model::SetAnimFrame(hModel_,0,100,1.0f);

	transEnemy_.scale_ = { 0.7f ,0.7f,0.7f};

	transEnemy_.position_.x = target_.x;
	transEnemy_.position_.y = target_.y;
	transEnemy_.position_.z = 5;

	SphereCollider* pSpher = new SphereCollider(XMFLOAT3(0,0.8f,0), 1.25f);
	AddCollider(pSpher);

}

//�X�V
void Enemy::Update()
{
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();



	RayCastData data;
	data.start = { transEnemy_.position_.x,0,transEnemy_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�


	if (data.hit)
	{
		transEnemy_.position_.y = -data.dist;
	}
	//transEnemy_.position_.z += 0.03f;

	//�v���C���[�̂��Ƃɋ삯�t������悤��
	//SetTargetPosition()


	target_ = ((Player*)FindObject("Player"))->GetPlayerPos();
	ChasePlayer(target_, 0.1f);

	transform_.position_ = transEnemy_.position_;
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

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack")
	{
		KillMe();
	}
}

void Enemy::ChasePlayer(XMFLOAT3& target_, float speed)
{
	vTarget_ = XMLoadFloat3(&target_);
	vPosition_ = XMLoadFloat3(&transEnemy_.position_);
	direction_ = XMVectorSubtract(vTarget_, vPosition_);	//�v���C���[�Ɍ������ĐL�тĂ���x�N�g��

	direction_ = XMVector3Normalize(direction_);//���K��


	XMVECTOR newVecPos_ = XMVectorAdd(vPosition_, XMVectorScale(direction_, speed));
	XMStoreFloat3(&transEnemy_.position_, newVecPos_);

	XMVECTOR playerToEnemy = XMVectorSubtract(vTarget_,vPosition_ );	//�v���C���[�Ɍ������ĐL�тĂ���x�N�g��
	float angle = atan2(XMVectorGetZ(playerToEnemy), XMVectorGetX(playerToEnemy));

	float angleDeg = XMConvertToDegrees(angle);

	transEnemy_.rotate_.y = angleDeg;
}

