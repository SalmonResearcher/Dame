#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "Stage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"
#include <string>

//�G���W���̋@�\
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

//#include "math.h"

namespace {
	//�v���C���[�̑傫���B
	// ��{�I�ɂ͒��������_�Ȃ̂�2�Ŋ���B
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	float mouseSens = 1;

    int attackWaitTime = 20;			//�U�����̑҂�����
	int attackCountDown = 0;			//�U�����̃J�E���g�_�E��
    const float JEWEL_WEIGHT = 0.01f;

    const float MAXSPEED = 0.15f;		//�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed = 0.0f;
	int walking = 1;
    int dash = 2;
    bool isHit;

	float jumpVelocity = 0.2f;
	float gravity = 0.01f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	float min = 0.9f;
	float max = 1.1f;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0), weight_(0), killCount_(0), jewelDeliver_(0), pStateManager_(nullptr)
	, attackEnd(false)
{
}

void Player::Initialize()
{
  	hModel_ = Model::Load("NewPlayer.fbx");
	assert(hModel_ >= 0);

	hSound_ = Audio::Load("SE/SordBig.wav", false, 2);

	hGetSound_ = Audio::Load("SE/GetJewel.wav", false, 1);

	// �X�e�[�g�}�l�[�W���[
	pStateManager_ = new StateManager(this);

	//�J����
	pCamera_ = Instantiate<PlayerCamera>(this);

	BoxCollider* collider = new BoxCollider({0,0.5,0},{1.0,1.0,1.0});
	AddCollider(collider);

	// ���炩���ߏ�ԃC���X�^���X�𐶐����ēo�^
	pStateManager_->AddState("IdleState", new IdleState(pStateManager_));
	pStateManager_->AddState("WalkState", new WalkState(pStateManager_));
	pStateManager_->AddState("RunState", new RunState(pStateManager_));
	pStateManager_->AddState("JumpState", new JumpState(pStateManager_));
	pStateManager_->AddState("AttackState", new AttackState(pStateManager_));
	pStateManager_->AddState("KnockbackState", new KnockbackState(pStateManager_));

	//�������
	pStateManager_->ChangeState("IdleState");
}

Player::~Player()
{
	SAFE_DELETE(pStateManager_);
}

void Player::Update()
{
	//�����_��
	jewelPitch = GenerateRandomFloat(min, max);

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	// �X�e�[�g�}�l�[�W���[�̍X�V
	pStateManager_->Update();


	RayCastData data;
	data.start = { transform_.position_.x,0,transform_.position_.z };   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	RayCastData play;
	play.start = { transform_.position_.x,transform_.position_.y + 0.5f,transform_.position_.z };   //���C�̔��ˈʒu
	play.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &play); //���C�𔭎�

	if (data.hit)
	{
		if (InputManager::IsJump() && !isJumping_)
		{
			Jump();
		}

		else if (isJumping_)
		{
			AddGravity();
		}

		//�W�����v��n�ʂɐG������
		if (play.dist < 0.4 && isJumping_)
		{
			moveY_ = 0.0f;
			isJumping_ = false;
		}

		//�W�����v���Ă��Ȃ�,�n�ɑ������Ȃ�
		if (!isJumping_ && play.hit)
		{
			transform_.position_.y = -data.dist;
		}

		//�n�ɑ������Ȃ��̂Ȃ��
		else if (!play.hit)
		{
			isJumping_ = true;
		}

		//Y���W�ړ�
		transform_.position_.y += moveY_;

	}

	// �X�e�[�W�O�ɗ����Ă��܂����ꍇ�̃��Z�b�g
	if (transform_.position_.y <= -100)
	{
		transform_.position_ = { 0, -data.dist, 0 };
		moveY_ = 0;
	}

	// Y���W�̍X�V
	transform_.position_.y += moveY_;

if (InputManager::IsWalk())
{
	speed += 0.006f;
	if (speed >= MAXSPEED)
	{
		speed = MAXSPEED;
	}
}
else
{
	speed -= 0.01f;
	if (speed <= 0)
	{
		speed = 0;
	}
}

	if (Input::IsMouseButton(1))
	{
		RotatePlayer();
	}

	// ���N���b�N�ƉE�N���b�N�������ɉ�����A�W���G����1�ȏ゠��ꍇ�ɃW���G���o���b�g�𐶐�
	if ((InputManager::IsShootJewel()) && jewelCount_ > 0)
	{
		JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());

		// �v���C���[�̉�]�s����쐬
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// �v���C���[�̑O���x�N�g�����擾
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);

		// �W���G���o���b�g�̕����A�ʒu�A��]��ݒ�
		pJB->BulletDirection(playerForwardVector);
		pJB->BulletPosition(transform_.position_);
		pJB->BulletRotate(transform_.rotate_);

		// �W���G���J�E���g������
		jewelCount_--;
	}

	//�d���̍ő�
	weight_ = 1 - min(0.99, jewelCount_ * JEWEL_WEIGHT);

	Debug::Log("���x��");
	Debug::Log(speed * dash * weight_, true);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::Walk()
{
	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, walking);
	RotatePlayer(moveVector);
}

void Player::Jump()
{
	//�n�ʂɑ������Ă���Ƃ�
	if (!isJumping_)
	{
		isJumping_ = true;
		moveY_ += jumpVelocity * weight_;
	}
}

void Player::Run()
{

	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, dash);
	RotatePlayer(moveVector);
}
void Player::AddGravity()
{
	//���R����
	moveY_ -= 0.01;

	if (moveY_ <= -0.2f)
	{
		moveY_ = -0.2f;
	}
}

void Player::AddMovement(XMVECTOR moveVector, float run)
{
	XMVECTOR newPosition = XMLoadFloat3(&transform_.position_) + (moveVector * run);
	XMStoreFloat3(&transform_.position_, newPosition);
}

// �ړ��v�Z���s���֐�
XMVECTOR Player::CalcMovementInput()
{
	// �ړ��x�N�g��
	XMVECTOR moveVector = XMVectorZero();
	XMVECTOR forwardMove = XMVectorZero();
	XMVECTOR sideMove = XMVectorZero();

	// �J������Y����]�s����擾
	XMMATRIX rotMatY = pCamera_->GetRotateY();



	// �O��̈ړ�
	if (InputManager::IsMoveForward())
	{
		forwardMove = XMVectorSet(0, 0, speed* weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}
	if (InputManager::IsMoveBackward())
	{
		forwardMove = XMVectorSet(0, 0, -speed * weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}

	// ���E�̈ړ�
	if (InputManager::IsMoveLeft())
	{
		sideMove = XMVectorSet(-speed * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}
	if (InputManager::IsMoveRight())
	{
		sideMove = XMVectorSet(speed * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}

	return moveVector;
}

void Player::Attacking()
{
	// �U���N�[���_�E����ݒ�
	if (attackCountDown == 0)
	{
		attackCountDown = attackWaitTime;
		attackEnd = false;
		Audio::Play(hSound_,2.0f);
	}
	else
	{
		attackCountDown--;
	}

	// �U���J�E���g�_�E��������̒l�ȉ��ŁA�U�����I�����Ă��Ȃ��ꍇ�ɍU���𐶐�(��₱��)
	if (attackCountDown <= 13 && !attackEnd)
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		// �v���C���[�̉�]�s����쐬
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// �v���C���[�̑O���x�N�g�����擾
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);

		pAtk->AttackDirection(playerForwardVector);
		pAtk->AttackPosition(transform_.position_);

		//�Ȃ��������̐�����ύX����Ɠ����蔻��̐���������...��B
		pAtk->SetDeleteTime(1);
	}

	// �U���J�E���g�_�E����0�ȉ��Ȃ�U���I��
	if (attackCountDown <= 0)
	{
		attackEnd = true;
	}
}

void Player::Knockback()
{
}

bool Player::IsJumping()
{
	return isJumping_;
}

bool Player::IsAttackEnd()
{
	return attackEnd;
}

void Player::OnCollision(GameObject* pTarget)
{
	isHit = false;

	if (pTarget->GetObjectName() == "Jewel")
	{
		//�����ŃG�t�F�N�g��
		Audio::Play(hGetSound_, true, jewelPitch, 1.0f);
		pTarget->KillMe();
		jewelCount_++;
	}

	if (pTarget->GetObjectName() == "JewelBox")
	{
		if (Input::IsKey(DIK_E))
		{
			if (onCollisionTime % 5 == 0 && !(jewelCount_ < 0))
			{
				jewelCount_--;
				jewelDeliver_++;
				onCollisionTime = 0;
			}
			onCollisionTime++;
		}
	}

	if (pTarget->GetObjectName() == "EnemyAttack")
	{
		knock = 0.8f;
		isJumping_ = true;
		moveY_ += 0.1f;

		// �v���C���[�̑O���x�N�g�����擾
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
		//vecPlayer_ += playerBackVector;
		//XMStoreFloat3(&transform_.position_, vecPlayer_);
	}
}

int Player::GetJewelCount()
{
	return jewelCount_;
}

void Player::KillCountUp()
{
	killCount_++;
}
int Player::GetKillCount()
{
	return killCount_;
}

XMVECTOR Player::GetKnockbackDirection()
{
	// �v���C���[�̑O���x�N�g�����擾
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	XMConvertToRadians(transform_.rotate_.y),XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
	//vecPlayer_ += playerBackVector;
	return playerBackVector;
}

float Player::GetSpeed()
{
	return speed;
}

float Player::GetWeight()
{
	return weight_;
}

void Player::RotatePlayer(XMVECTOR moveVector)
{
	// �ړ��x�N�g�����琅�������̊p�x���v�Z
	XMFLOAT3 moveVecFloat3;
	XMStoreFloat3(&moveVecFloat3, moveVector);

	if (moveVecFloat3.x != 0 || moveVecFloat3.z != 0) {
		float playerYaw = atan2f(moveVecFloat3.x, moveVecFloat3.z);
		transform_.rotate_.y = XMConvertToDegrees(playerYaw);
	}

	// �v���C���[�̉�]�s����쐬
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));
}

void Player::RotatePlayer()
{
	// �J�����̉�]�s�񂩂�v���C���[�̐��������̊p�x�����߂�
	XMFLOAT4X4 cameraRot = pCamera_->GetCameraRotateMatrix();
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	// �v���C���[�̉�]���X�V
	transform_.rotate_.y = XMConvertToDegrees(playerYaw);

	// �v���C���[�̉�]�s����쐬
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));
}

float Player::GenerateRandomFloat(float min, float max) 
{
	float random = static_cast<float>(rand()) / RAND_MAX; // 0.0����1.0�͈̗̔͂����𐶐�
	return min + random * (max - min); // min����max�͈̔͂ɃX�P�[�����O
}