#include "Player.h"
#include "Attack.h"
#include "Enemy.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), dash(1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	BoxCollider* collider = new BoxCollider({0,0.5,0},{1.0,1.0,1.0});
	AddCollider(collider);

}

void Player::Update()
{

	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = {tPlayer_.position_.x,0,tPlayer_.position_.z};   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hStage_, &data); //���C�𔭎�

	RayCastData play;
	play.start = { tPlayer_.position_.x,tPlayer_.position_.y+0.3f,tPlayer_.position_.z };   //���C�̔��ˈʒu
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
			tPlayer_.position_.y = -data.dist;
		}

		tPlayer_.position_.y += moveY;
	}



	if (Input::IsKey(DIK_LSHIFT))
		dash = 2;

	else
		dash = 1;

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
	XMVECTOR nowVec = XMLoadFloat3(& tPlayer_.position_);			//���̃J�����ʒu���W
	XMVECTOR frontMove = XMVectorSet(0, 0, speed_ * dash, 0);		//z���W�ɓ������x
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y����]�s���frontmove�x�N�g���֕ϊ�

	//�㉺���E��]
	XMVECTOR upDownMove = XMVectorSet(0, speed_ * dash, 0, 0);
	upDownMove = XMVector3TransformCoord(upDownMove, rotMatY);
	XMVECTOR leftRightMove = XMVectorSet(speed_ * dash, 0, 0, 0);
	leftRightMove = XMVector3TransformCoord(leftRightMove, rotMatY);

	//�v���C���[�������ňړ�������
	vecPlayer_ = XMLoadFloat3(&tPlayer_.position_);

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
		vecPlayer_ -= leftRightMove;
	}

	if (Input::IsKey(DIK_D))
	{
		vecPlayer_ += leftRightMove;
	}

	XMStoreFloat3(&movePlayer, vecPlayer_);

	XMStoreFloat3(&tPlayer_.position_, vecPlayer_);


	//�J�����ړ�
	XMStoreFloat3(&tCamera.position_, nowVec);

	//�J�����{��
	XMVECTOR vCam = { 0,2,-10,0 };

	//�J���������_
	XMFLOAT3 camTarget = tPlayer_.position_;

	//1F�O�̍���
	static 	XMFLOAT3 prevPos = tPlayer_.position_;

	smoothCam.x = camTarget.x;
	smoothCam.y = camTarget.y - (camTarget.y - prevPos.y) / 2;
	smoothCam.z = camTarget.z;

	if (smoothCam.x < 0.01f)
		smoothCam.x = camTarget.x;

	if ((camTarget.y - prevPos.y) / 2 < 0.01f)
		smoothCam.y = camTarget.y;

	if (smoothCam.z < 0.01f)
		smoothCam.z = camTarget.z;

	prevPos.y = smoothCam.y;

	//Debug::Log("prev.y = ");
	//Debug::Log(prevPos.y, true);
	//Debug::Log("now.y = ");
	//Debug::Log(camTarget.y, true);
	Camera::SetTarget(smoothCam);

	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);


	//�J�������W�ύX
	XMStoreFloat3(&Camposition_, nowVec + vCam);

	//Debug::Log(Camposition_.x, true);
	//Debug::Log(Camposition_.y, true);
	//Debug::Log(Camposition_.z,true);


	RayCastData cam;
	cam.start = camTarget;  //���C�̔��ˈʒu
	cam.dir = Camposition_;       //���C�̕���
	Model::RayCast(hStage_, &cam); //���C�𔭎�



	//�J�����ړ�
	Camera::SetPosition(Camposition_);

	transform_ = tPlayer_;

	// �J�����̉�]�s����쐬
	XMMATRIX cameraRotMat = rotMatX * rotMatY;

	// �J�����̉�]�s��𒊏o
	XMFLOAT4X4 cameraRot;
	XMStoreFloat4x4(&cameraRot, cameraRotMat);

	// �J�����̌����Ƀv���C���[�������邽�߂̉�]�p�x�����߂�
	float playerYaw = atan2f(-cameraRot._13, cameraRot._11);

	// �v���C���[�̉�]���X�V
	tPlayer_.rotate_.y = XMConvertToDegrees(playerYaw);

	//playerYaw��+-1.5�����傤�ǉE�����獶�����Ċ���
	//Debug::Log(playerYaw);

	attackStart = playerYaw + 1.5;
	attackEnd = playerYaw - 1.5;

	Debug::Log("x = ");
	Debug::Log(tPlayer_.rotate_.x, true);

	Debug::Log("y = ");
	Debug::Log(tPlayer_.rotate_.y, true);

	Debug::Log("z = ");
	Debug::Log(tPlayer_.rotate_.z, true);

	if (Input::IsKeyDown(DIK_E))
	{
		Attack* pAtk = Instantiate<Attack>(GetParent());
		pAtk->SetMove(camTarget);
		pAtk->SetPosition(camTarget);
	}

	if (Input::IsMouseButtonDown(0))
	{
		if ((Enemy*)FindObject("Enemy") != nullptr)
		{
			hEnemy_ = ((Enemy*)FindObject("Enemy"))->GetModelHandle();

			RayCastData attack;
			attack.start = { tPlayer_.position_ };   //���C�̔��ˈʒu
			attack.dir = XMFLOAT3{ 0,0.5f,1 };       //���C�̕���
			Model::RayCast(hEnemy_, &attack); //���C�𔭎�

			if (/*attack.dist <= 2.0f &&*/ attack.hit)
			{
				((Enemy*)FindObject("Enemy"))->KillMe();
			}

		}


		}

	}



void Player::Draw()
{
	Model::SetTransform(hModel_, tPlayer_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::StageRay()
{
	if ((Stage*)FindObject("Stage") != nullptr)
	{
		hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();
		
		RayCastData down;
	}

}
