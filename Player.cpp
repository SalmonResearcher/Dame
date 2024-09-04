#include "Player.h"
#include "Attack.h"
#include "Jewel.h"
#include "JewelBullet.h"
#include "Enemy.h"
#include "Stage.h"
#include "TutorialStage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"
#include "Global.h"
#include <string>

//�G���W���̋@�\
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include "Engine/Debug.h"
//#include "math.h"

namespace {
	//�v���C���[�̑傫���B
	// ��{�I�ɂ͒��������_�Ȃ̂�2�Ŋ���B
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	// �U�����̑҂����ԂƃJ�E���g�_�E��
	const int ATTACK_WAIT_TIME = 20;


	//����O���[�o���̂ق�����������..?
    const float JEWEL_WEIGHT = 0.01f;

	// �v���C���[�̉����x
	const float PLAYER_ACCELERATION = 0.006f;

	const float MAX_SPEED = 0.15f;

	const int WALKING_SPEED = 1;
	const int DASH_SPEED = 2;

	const float JUMP_VELOCITY = 0.4f;
	const float GRAVITY = 0.02f;
	const float MAX_GRAVITY = 0.5f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	//���̃s�b�`
	float min = 0.9f;
	float max = 1.1f;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0), weight_(0), killCount_(0), jewelDeliver_(0), pStateManager_(nullptr)
	, attackEnd_(false)
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
	jewelPitch_ = GenerateRandomFloat(min, max);

	hStage_ = SetStageHandle();

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

	Debug::Log(play.dist, true);

	// �n�ʗL��
	if (data.hit)
	{
		// �W�����v���Ă��Ȃ��Ƃ�
		if (InputManager::IsJump() && !isJumping_)
		{
			Jump();
		}
		// �W�����v���Ă�����
		else if (isJumping_)
		{
			AddGravity();

			// �W�����v��n�ʂɐG������
			if (play.dist < 0.498f)
			{
				moveY_ = 0.0f;
				isJumping_ = false;
				transform_.position_.y = -data.dist;  // �n�ʂɈʒu���Œ�
			}
		}
		else // �W�����v���Ă��Ȃ�, �n�ɑ������Ȃ�
		{
			if (play.hit)
			{
				transform_.position_.y = -data.dist;
			}
			else // �n�ɑ������Ȃ��̂Ȃ��
			{
				isJumping_ = true;
			}
		}
	}
	else // �n�ʂ��Ȃ��ꍇ
	{
		AddGravity();
	}

	// �X�e�[�W�O�ɗ����Ă��܂����ꍇ�̃��Z�b�g
	if (transform_.position_.y <= -90)
	{
		transform_.position_ = { 0, -data.dist, 0 };
		moveY_ = 0;
	}

	// Y���W�̍X�V
	transform_.position_.y += moveY_;

	// �ړ����x�̊Ǘ�
	if (InputManager::IsWalk())
	{
		speed_ += PLAYER_ACCELERATION;
		if (speed_ >= MAX_SPEED)
		{
			speed_ = MAX_SPEED;
		}
	}
	else
	{
		speed_ -= 0.01f;
		if (speed_ <= 0)
		{
			speed_ = 0;
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
	AddMovement(moveVector, WALKING_SPEED);
	RotatePlayer(moveVector);
}

void Player::Jump()
{
	//�n�ʂɑ������Ă���Ƃ�
	if (!isJumping_)
	{
		isJumping_ = true;
		moveY_ += JUMP_VELOCITY * weight_;
	}
}

void Player::Run()
{

	XMVECTOR moveVector = CalcMovementInput();
	AddMovement(moveVector, DASH_SPEED);
	RotatePlayer(moveVector);
}
void Player::AddGravity()
{
	//���R����
	moveY_ -= GRAVITY;

	if (moveY_ <= -MAX_GRAVITY)
	{
		moveY_ = -MAX_GRAVITY;
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
		forwardMove = XMVectorSet(0, 0, speed_* weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}
	if (InputManager::IsMoveBackward())
	{
		forwardMove = XMVectorSet(0, 0, -speed_ * weight_, 0);
		forwardMove = XMVector3TransformCoord(forwardMove, rotMatY);
		moveVector += forwardMove;
	}

	// ���E�̈ړ�
	if (InputManager::IsMoveLeft())
	{
		sideMove = XMVectorSet(-speed_ * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}
	if (InputManager::IsMoveRight())
	{
		sideMove = XMVectorSet(speed_ * weight_, 0, 0, 0);
		sideMove = XMVector3TransformCoord(sideMove, rotMatY);
		moveVector += sideMove;
	}

	return moveVector;
}

void Player::Attacking()
{
	// �U���N�[���_�E����ݒ�
	if (attackCountDown_ == 0)
	{
		attackCountDown_ = ATTACK_WAIT_TIME;
		attackEnd_ = false;
		Audio::Play(hSound_,true,2.0f,Global::SE_VOLUME);
	}
	else
	{
		attackCountDown_--;
	}

	// �U���J�E���g�_�E��������̒l�ȉ��ŁA�U�����I�����Ă��Ȃ��ꍇ�ɍU���𐶐�(��₱��)
	if (attackCountDown_ <= 13 && !attackEnd_)
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
	if (attackCountDown_ <= 0)
	{
		attackEnd_ = true;
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
	return attackEnd_;
}

void Player::OnCollision(GameObject* pTarget)
{
	isHit_ = false;

	if (pTarget->GetObjectName() == "Jewel")
	{
		((Jewel*)FindObject("Jewel"))->DestroyVFX();
		Audio::Play(hGetSound_, true, jewelPitch_, Global::SE_VOLUME);
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
	return speed_;
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

//�����_����Float��min�`max�̒l���Z�o
float Player::GenerateRandomFloat(float min, float max) 
{
	float random = static_cast<float>(rand()) / RAND_MAX; // 0.0����1.0�͈̗̔͂����𐶐�
	return min + random * (max - min); // min����max�͈̔͂ɃX�P�[�����O
}

int Player::SetStageHandle()
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