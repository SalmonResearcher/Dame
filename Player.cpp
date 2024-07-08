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

//
//#include "math.h"

namespace {
	//�v���C���[�̑傫���B
// ��{�I�ɂ͒��������_�Ȃ̂�2�Ŋ���B
	const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

	float mouseSens = 1;

    int attackWaitTime = 20;	//�U�����̑҂�����
	int attackCountDown = 0;	//�U�����̃J�E���g�_�E��
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed = 0.0f;
	int walking = 1;
    int dash = 2;
    bool isHit;

	float jumpVelocity = 5.0f;
	float gravity = 0.01f;

    int onCollisionTime = 0;
	bool isKockBack = false;
	float knock;

	std::string debugstr = "null";

	RayCastData downRay;
	RayCastData play;
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
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	// �X�e�[�g�}�l�[�W���[�̍X�V
	pStateManager_->Update();


	//Y���W0���牺�Ɍ��������C�i������Ƃ��ɕK�v�j
	downRay.start = {transform_.position_.x,0,transform_.position_.z};   //���C�̔��ˈʒu
	downRay.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &downRay); //���C�𔭎�

	//�v���C���[�̓������΂����C
	play.start = { transform_.position_.x,transform_.position_.y+0.3f,transform_.position_.z };   //���C�̔��ˈʒu
	play.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &play); //���C�𔭎�
	
	if (downRay.hit)
	{
		if (downRay.hit)
		{
			if (!isJumping_)
			{
				// �W�����v
				if (Input::IsKeyDown(DIK_SPACE))
				{
					isJumping_ = true;
					moveY_ = 0.2f; // �W�����v�����x��ݒ�
				}
			}
			else
			{
				// ���R����
				moveY_ -= 0.01f; // �d�͂�K�p

				// �ő嗎�����x�𐧌�
				if (moveY_ <= -0.25f)
				{
					moveY_ = -0.25f;
				}
			}

			// �n�ʂƂ̏Փ˂����o
			if (play.dist <= 0.25f && isJumping_)
			{
				moveY_ = 0.0f;
				isJumping_ = false;
			}

			// �n�ʂɂ��鎞�̈ʒu����
			if (!isJumping_)
			{
				transform_.position_.y = -downRay.dist;
			}

			// Y���W�̍X�V
			transform_.position_.y += moveY_;
		}

		// �X�e�[�W�O�ɗ����Ă��܂����ꍇ�̃��Z�b�g
		if (transform_.position_.y <= -100)
		{
			transform_.position_ = { 0, -downRay.dist, 0 };
		}
	}

	/*
	if (Input::IsKey(DIK_LSHIFT))
		dash_ = 2;

	else
		dash_ = 1;

	static bool debug = true;



	//�}�E�X���x
	{
		if (Input::IsKeyDown(DIK_UP))
		{
			if (Input::IsKey(DIK_LSHIFT))
				mouseSens += 0.5f;
			else
				mouseSens += 0.1f;
		}

		if (Input::IsKeyDown(DIK_DOWN))
		{
			if (Input::IsKey(DIK_LSHIFT))
				mouseSens -= 0.5f;
			else
				mouseSens -= 0.1f;
		}
	}
	//�}�E�X�ʒu�Œ�
	if (debug)
		SetCursorPos(800, 400);

	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 camMove = { 0,0,0 };

	//�}�E�X�̈ړ���
	move.x += Input::GetMouseMove().x * mouseSens;
	move.y += Input::GetMouseMove().y * mouseSens;
	move.z += Input::GetMouseMove().z * mouseSens;	//�}�E�X�z�C�[��



	//�}�E�X�̈ړ��ʂɉ����ăJ��������]������
	camMove.y = move.x;
	camMove.x = move.y;

	

	//�}�E�X�Z���V�e�B�r���e�B
	camMove.x *= 0.1;
	camMove.y *= 0.1;

	//�������������Ȃ��悤��
	if (camMove.x >= 75)
	{
		camMove.x = 75;
		move.y = 750;
	}

	//������������Ȃ�
	if (camMove.x <= -85)
	{
		camMove.x = -85;
		move.y = -850;
	}

	tCamera.rotate_ = camMove;
	*/

	//�v���C���[�ړ���
	/*
	//Y���̉�]�s��
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(tCamera.rotate_.y));

	//X���̉�]��
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(tCamera.rotate_.x));

	//�ړ��x�N�g��
	XMVECTOR nowVec = XMLoadFloat3(& transform_.position_);			//���̃J�����ʒu���W
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash_ * weight_, 0);		//z���W�ɓ������x
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y����]�s���frontmove�x�N�g���֕ϊ�

	//���E
	XMVECTOR sideVec_ = XMVectorSet(speed_ * dash_ * weight_, 0, 0, 0);
	sideVec_ = XMVector3TransformCoord(sideVec_, rotMatY);

	//�v���C���[�������ňړ�������
	vecPlayer_ = XMLoadFloat3(&transform_.position_);

	if ((Input::IsKey(DIK_W)|| Input::IsKey(DIK_A)|| Input::IsKey(DIK_S)|| Input::IsKey(DIK_D)))
	{
		speed_ += 0.01f;
		if (speed_ >= MAXSPEED)
			speed_ = MAXSPEED;
	}
	else
	{
		speed_ -= 0.01f;
		if (speed_ <= 0.0f)
		{
			speed_ = 0.0f;
		}
	}

	//�v���C���[�ړ�
	if (Input::IsKey(DIK_W))
	{
		vecPlayer_ += frontMove;

	}

	if (Input::IsKey(DIK_S))
	{
		vecPlayer_ -= frontMove;
	}

	if (Input::IsKey(DIK_A))
	{
		vecPlayer_ -= sideVec_;
	}

	if (Input::IsKey(DIK_D))
	{
		vecPlayer_ += sideVec_;
	}

	XMVector3Normalize(vecPlayer_);
	XMStoreFloat3(&transform_.position_, vecPlayer_);
	*/

	/*
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);			//���̃J�����ʒu���W

	//�J�����ړ�
	XMStoreFloat3(&tCamera.position_, nowVec);

	//�J�����{��
	XMVECTOR vCam = { 0,2,-10,0 };

	//�J���������_
	XMFLOAT3 camTarget = transform_.position_;

	Camera::SetTarget(camTarget);

	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//�J�������W�ύX
	XMStoreFloat3(&Camposition_, nowVec + vCam);
	
	//�J�����ړ�
	Camera::SetPosition(Camposition_);

	*/

/*
	XMFLOAT4X4 cameraRot = pCamera_->GetCameraRotateMatrix();

	//�v���C���[�̐��������̊p�x�����߂�
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	//// �v���C���[�̉�]���X�V
	transform_.rotate_.y = XMConvertToDegrees(playerYaw);

	// �v���C���[�̉�]�s����쐬
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
		XMConvertToRadians(transform_.rotate_.y),
		XMConvertToRadians(transform_.rotate_.z));

	// �v���C���[�̑O���x�N�g�����擾
	XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), playerRotMat);
	*/

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

	////�������������
	//if (Input::IsMouseButtonDown(0) && !(Input::IsMouseButton(1)))
	//{
	//	Attack* pAtk = Instantiate<Attack>(GetParent());
	//	//pAtk->SetMove(camTarget);
	//	//pAtk->SetPosition(camTarget);
	//	pAtk->SetTime(2);

	//}
	//else if (Input::IsMouseButtonDown(0) && (Input::IsMouseButton(1)) && jewelCount_ > 0)
	//{
	//	JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());
	//	// �v���C���[�̉�]�s����쐬
	//	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	//		XMConvertToRadians(transform_.rotate_.y),
	//		XMConvertToRadians(transform_.rotate_.z));

	//	// �v���C���[�̑O���x�N�g�����擾
	//	XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),playerRotMat);
	//	pJB->BulletDirection(playerForwardVector);
	//	pJB->BulletPosition(transform_.position_);
	//	pJB->BulletRotate(transform_.rotate_);
	//	jewelCount_--;
	//}

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
	//if (currentState_) {
	//	delete currentState_;
	//}
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
	if (attackCountDown <= 0)
	{
		attackCountDown = attackWaitTime;
		attackEnd = false;
	}
	else
	{
		attackCountDown--;
	}

	// �U���J�E���g�_�E��������̒l�ȉ��ŁAAim���Ă��炸�A�U�����I�����Ă��Ȃ��ꍇ�ɍU���𐶐�
	if (attackCountDown <= 8 && !InputManager::IsAim && !attackEnd)
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		// �U���̈ړ���ƈʒu��ݒ�i��: pAtk->SetMove(camTarget);�j
		// pAtk->SetPosition(camTarget);
		pAtk->SetTime(4);
	}

	// ���N���b�N�ƉE�N���b�N�������ɉ�����A�W���G����1�ȏ゠��ꍇ�ɃW���G���o���b�g�𐶐�
	if (InputManager::IsAttack() && InputManager::IsAim() && jewelCount_ > 0)
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
		//isJumping = true;
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
