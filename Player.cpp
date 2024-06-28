#include "Player.h"
#include "Attack.h"
#include "JewelBullet.h"
#include "Enemy/Enemy.h"
#include "math.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"

#include "Engine/SceneManager.h"

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
    short moveSpeed;
    short dash_;
    bool isHit;

    int onCollisionTime = 0;


	Transform tCamera;  //�J�����̃g�����X�t�H�[��

	XMVECTOR vecPlayer_;    //�v���C���[�̐i��ł�������x�N�g��
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
	:GameObject(parent, "Player"), hModel_(-1)//currentState_(nullptr)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("NewPlayer.fbx");
	assert(hModel_ >= 0);

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

	//�������
	//ChangeState(new IdleState());
	Model::SetAnimFrame(hModel_,fastMove.startFrame,fastMove.endFrame,fastMove.animSpeed);
}

void Player::Update()
{

	//if (currentState_) {
	//	currentState_->Update(this);
	//}

	// �J�����̍X�V
	//camera_.Update(transform_);

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
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping)
		{
			isJumping = true;
			moveY_ += 0.2f * weight_;
		}
		
		else if (isJumping)
		{
			//���R����
			moveY_ -= 0.01;

			if (moveY_ <= -0.25f)
			{
				moveY_ = -0.25f;
			}
		}

		//�W�����v��n�ʂɐG������
		if (play.dist <= 0.25 && isJumping)
		{
			moveY_ = 0.0f;
			isJumping = false;
		}

		//�W�����v���Ă��Ȃ�,�n�ɑ������Ȃ�
		if (!isJumping && play.hit)
		{
			transform_.position_.y = -data.dist;
		}

		//�n�ɑ������Ȃ��̂Ȃ��
		else if (!play.hit)
		{
			isJumping = true;
		}

		//Y���W�ړ�
		transform_.position_.y += moveY_;
	}



	if (Input::IsKey(DIK_LSHIFT))
		dash_ = 2;

	else
		dash_ = 1;

	static bool debug = true;


	if (Input::IsKeyDown(DIK_RSHIFT))
	{
		if (debug)
		{
			debug = false;
		}
		else
		{
			debug = true;
		}
	}

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

	transform_ = transform_;

	// �J�����̉�]�s����쐬
	XMMATRIX cameraRotMat = rotMatX * rotMatY;

	// �J�����̉�]�s��𒊏o
	XMFLOAT4X4 cameraRot;

	//XMFloat4*4�Ɋi�[
	XMStoreFloat4x4(&cameraRot, cameraRotMat);

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
		pAtk->SetMove(camTarget);
		pAtk->SetPosition(camTarget);
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
		isJumping = true;
		moveY_ += 0.1f;

		// �v���C���[�̑O���x�N�g�����擾
		XMMATRIX playerRotMat = XMMatrixRotationRollPitchYaw(XMConvertToRadians(transform_.rotate_.x),
			XMConvertToRadians(transform_.rotate_.y),
			XMConvertToRadians(transform_.rotate_.z));

		XMVECTOR playerBackVector = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), playerRotMat);
		vecPlayer_ += playerBackVector;
		XMStoreFloat3(&transform_.position_, vecPlayer_);

	}
}

XMVECTOR Player::GetPlayerVec()
{
		return vecPlayer_;
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
	vecPlayer_ += playerBackVector;

	return vecPlayer_;
}
