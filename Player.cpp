#include "Player.h"
#include "Stage.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), dash(1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

}

void Player::Update()
{
	Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
	int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

	RayCastData data;
	data.start = {tPlayer_.position_.x,0,tPlayer_.position_.z};   //���C�̔��ˈʒu
	data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hGroundModel, &data); //���C�𔭎�

	RayCastData play;
	play.start = { tPlayer_.position_.x,tPlayer_.position_.y+0.3f,tPlayer_.position_.z };   //���C�̔��ˈʒu
	play.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
	Model::RayCast(hGroundModel, &play); //���C�𔭎�
	
	if (data.hit)
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && !isJumping)
		{
			isJumping = true;
			moveY += 0.5;
		}
		
		else if (isJumping)
		{
			//���R����
			moveY -= 0.03;

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
	//���f�o�b�N�p
	//Debug::Log("isJumping = ");
	//Debug::Log(isJumping, true);
	//Debug::Log("play.dist = ");
	//Debug::Log(play.dist, true);
	//���f�o�b�O�p
	

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
	//�}�E�X�ʒu�Œ�
	if (debug)
		SetCursorPos(800, 400);


	static XMFLOAT3 move = { 0,0,0 };
	static XMFLOAT3 camMove = { 0,0,0 };

	//�}�E�X�̈ړ���
	move.x += Input::GetMouseMove().x;
	move.y += Input::GetMouseMove().y;
	move.z += Input::GetMouseMove().z;	//�}�E�X�z�C�[��

	//�}�E�X�̈ړ��ʂɉ����ăJ��������]������
	camMove.y = move.x;
	camMove.x = move.y;

	

	//�}�E�X�Z���V�e�B�r���e�B
	camMove.x *= 0.1;
	camMove.y *= 0.1;

	//������������Ȃ��悤��
	if (camMove.x >= 69)
	{
		camMove.x = 69;
		move.y = 690;
	}

	//�������������Ȃ�
	if (camMove.x <= -20)
	{
		camMove.x = -20;
		move.y = -200;
	}

	tCamera.rotate_ = camMove;

	//Y���̉�]�s��
	XMMATRIX rotMatY = XMMatrixRotationY(XMConvertToRadians(tCamera.rotate_.y));

	//X���̉�]��
	XMMATRIX rotMatX = XMMatrixRotationX(XMConvertToRadians(tCamera.rotate_.x));

	//�ړ��x�N�g��
	XMVECTOR nowVec = XMLoadFloat3(& tPlayer_.position_);			//���̃J�����ʒu���W
	XMVECTOR frontMove = XMVectorSet(0, 0, SPEED * dash, 0);		//z���W�ɓ������x
	frontMove = XMVector3TransformCoord(frontMove, rotMatY);	//Y����]�s���frontmove�x�N�g���֕ϊ�

	//�㉺���E��]
	XMVECTOR upDownMove = XMVectorSet(0, SPEED * dash, 0, 0);
	upDownMove = XMVector3TransformCoord(upDownMove, rotMatY);
	XMVECTOR leftRightMove = XMVectorSet(SPEED * dash, 0, 0, 0);
	leftRightMove = XMVector3TransformCoord(leftRightMove, rotMatY);

	//�v���C���[�������ňړ�������
	vecPlayer_ = XMLoadFloat3(&tPlayer_.position_);
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


	XMStoreFloat3(&tPlayer_.position_, vecPlayer_);

	//�J�����ړ�
	XMStoreFloat3(&tCamera.position_, nowVec);

	//�J�����{��
	XMVECTOR vCam = { 0,0,-10,0 };

	//�J���������_
	XMFLOAT3 camTarget = tPlayer_.position_;
	//camTarget.z += 2;
	Camera::SetTarget(camTarget);
	vCam = XMVector3TransformCoord(vCam, rotMatX * rotMatY);

	//�J�������W�ύX
	XMStoreFloat3(&Camposition_, nowVec + vCam);

	RayCastData cam;
	cam.start = camTarget;  //���C�̔��ˈʒu
	cam.dir = Camposition_;       //���C�̕���
	Model::RayCast(hGroundModel, &cam); //���C�𔭎�

	Debug::Log("cam to mat");
	Debug::Log(Camposition_.z, true);
	tPlayer_.position_.y = -data.dist;

	//�J�����ړ�
	Camera::SetPosition(Camposition_);

	

}

void Player::Draw()
{
	Model::SetTransform(hModel_, tPlayer_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
