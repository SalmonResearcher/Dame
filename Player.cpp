#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "Stage.h"
#include "StateManager.h"
#include "PlayerState.h"
#include "PlayerCamera.h"

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

    float attackStart;
    float attackEnd;
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed_ = 0;
    int dash_ = 1;
    bool isHit;

    int onCollisionTime = 0;


	Transform tCamera;  //�J�����̃g�����X�t�H�[��

	XMFLOAT3 movePlayer;

	XMFLOAT3 Camposition_;
	XMFLOAT3 smoothCam;

	bool isKockBack = false;
	float knock;

	struct AnimFrame {
		int startFrame;
		int endFrame;
		int animSpeed;
	};
	AnimFrame wait, slowMove, move, fastMove, attack;

}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), hStage_(-1), hEnemy_(-1), isJumping_(false),
	moveY_(0), jewelCount_(0),weight_(0),killCount_(0),jewelDeliver_(0),pStateManager_(nullptr)
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

	{
		wait.startFrame = 0;
		wait.endFrame = 120;
		wait.animSpeed = 1;

		slowMove.startFrame = 140;
		slowMove.endFrame = 230;
		slowMove.animSpeed = 1;

		move.startFrame = 280;
		move.endFrame = 330;
		move.animSpeed = 1;

		fastMove.startFrame = 340;
		fastMove.endFrame = 365;
		fastMove.animSpeed = 1;

		attack.startFrame = 370;
		attack.endFrame = 390;
		attack.animSpeed = 1;
	}


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
	// �X�e�[�g�}�l�[�W���[�̍X�V
	pStateManager_->Update();
	if (isJumping_)
	{
		//juuryoku
	}

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = {transform_.position_.x,0,transform_.position_.z};   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	RayCastData play;
	play.start = { transform_.position_.x,transform_.position_.y+0.3f,transform_.position_.z };   //���C�̔��ˈʒu
	play.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &play); //���C�𔭎�
	
	if (data.hit)
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping_)
		{
			isJumping_ = true;
			moveY_ += 0.2f * weight_;
		}
		
		else if (isJumping_)
		{
			//���R����
			moveY_ -= 0.01;

			if (moveY_ <= -0.25f)
			{
				moveY_ = -0.25f;
			}
		}

		//�W�����v��n�ʂɐG������
		if (play.dist <= 0.25 && isJumping_)
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


	//�������������
	if (Input::IsMouseButtonDown(0) && !(Input::IsMouseButton(1)))
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		//pAtk->SetMove(camTarget);
		//pAtk->SetPosition(camTarget);
		pAtk->SetTime(2);

	}
	else if (Input::IsMouseButtonDown(0) && (Input::IsMouseButton(1)) && jewelCount_ > 0)
	{
		JewelBullet* pJB = InstantiateFront<JewelBullet>(GetParent());
		// �v���C���[�̉�]�s����쐬
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		// �v���C���[�̑O���x�N�g�����擾
		XMVECTOR playerForwardVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),playerRotMat);
		pJB->BulletDirection(playerForwardVector);
		pJB->BulletPosition(transform_.position_);
		pJB->BulletRotate(transform_.rotate_);
		jewelCount_--;
	}

	//�d���̍ő�
	weight_ = 1 - min(0.99, jewelCount_ * JEWEL_WEIGHT);

	transform_ = transform_;
	transform_.rotate_ = transform_.rotate_;
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
	AddMovement(CalcMovementInput(),dash_);
}

void Player::Jump()
{
}

void Player::Run()
{
}
void Player::AddGravity()
{

}
void Player::AddMovement(XMVECTOR moveVector, float run)
{
	XMStoreFloat3(&transform_.position_, moveVector * run);
}

// �ړ��v�Z���s���֐�
XMVECTOR Player::CalcMovementInput()
{
	if ((Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D)))
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



	// �v�Z����
	XMVECTOR vecPlayer_;

	XMMATRIX rotMatY = pCamera_->GetRotateY();

	//�ړ��x�N�g��
	XMVECTOR nowVec = XMLoadFloat3(&transform_.position_);			//���̃J�����ʒu���W
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash_ * weight_, 0);		//z���W�ɓ������x
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y����]�s���frontmove�x�N�g���֕ϊ�

	//���E
	XMVECTOR sideVec_ = XMVectorSet(speed_ * dash_ * weight_, 0, 0, 0);
	sideVec_ = XMVector3TransformCoord(sideVec_, rotMatY);

	//�v���C���[�������ňړ�������
	vecPlayer_ = XMLoadFloat3(&transform_.position_);

	// Player�N���X��Move�֐����̈ꕔ
	if (InputManager::IsMoveForward())
	{
		vecPlayer_ += frontMove;
	}
	if (InputManager::IsMoveLeft())
	{
		vecPlayer_ -= sideVec_;
	}
	if (InputManager::IsMoveBackward())
	{
		vecPlayer_ -= frontMove;
	}
	if (InputManager::IsMoveRight())
	{
		vecPlayer_ += sideVec_;
	}


	if (speed_ >= MAXSPEED)
	{
		speed_ = MAXSPEED;
	}

	XMVector3Normalize(vecPlayer_);
	return vecPlayer_;
}

void Player::Attacking()
{
}

void Player::Knockback()
{
}

bool Player::IsJumping()
{
	return false;
}


//void Player::ChangeState(PlayerState* newState)
//{
//	if (currentState_) {
//		currentState_->Exit(this);
//		delete currentState_;
//	}
//	currentState_ = newState;
//	if (currentState_) {
//		currentState_->Enter(this);
//	}
//}

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

XMVECTOR  Player::GetKnockbackDirection()
{
	// �v���C���[�̑O���x�N�g�����擾
	XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
	XMConvertToRadians(transform_.rotate_.y),XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
	//vecPlayer_ += playerBackVector;;
	return playerBackVector;
}