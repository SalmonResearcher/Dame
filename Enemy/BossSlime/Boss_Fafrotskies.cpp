#include "Boss_Fafrotskies.h"
#include "../../Stage.h"
#include "../../Player.h"
#include "../../Engine/Input.h"
#include "../../Engine/Model.h"
#include "../../Engine/SphereCollider.h"

#include "../../Engine/Debug.h"
//コンストラクタ
Fafro::Fafro(GameObject* parent)
	:GameObject(parent, "Fafro"), hModel_(-1), hStage_(-1), isJumping(false), startFrame(0), endFrame(100), animeSpeed(1),gloTime(0)
{
}

//デストラクタ
Fafro::~Fafro()
{
}

//初期化
void Fafro::Initialize()
{
	hModel_ = Model::Load("Boss_Slime.fbx");
	assert(hModel_ >= 0);
	Model::SetAnimFrame(hModel_, 0, 90, 1.0f);


	transFafro_.position_.x = 5;
	transFafro_.position_.y = target_.y;
	transFafro_.position_.z = -5;

	SphereCollider* pSpher = new SphereCollider(XMFLOAT3(0, 0.8f, 0), 1.25f);
	AddCollider(pSpher);

}

//更新
void Fafro::Update()
{
	hStage_ = ((Stage*)FindObject("Stage"))->GetModelHandle();

	RayCastData data;
	data.start = { transFafro_.position_.x,0,transFafro_.position_.z };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	RayCastData play;
	play.start = { transFafro_.position_.x,transFafro_.position_.y + 0.3f,transFafro_.position_.z };   //レイの発射位置
	play.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &play); //レイを発射

	if (data.hit)
	{
		if (play.dist <= 0.25 && isJumping)
		{
			moveY = 0.0f;
			isJumping = false;
		}

		if (!isJumping)
		{
			transFafro_.position_.y = -data.dist;
		}

		transFafro_.position_.y += moveY;
	}
	

	//プレイヤーのもとに駆け付けられるように
	//SetTargetPosition()

	if (Input::IsKeyDown(DIK_X))
	{
		Model::SetAnimFrame(hModel_, 100, 135, 1.0f);
	}
	if (Input::IsKeyDown(DIK_Y))
	{
		Model::SetAnimFrame(hModel_, 150, 170, 1.0f);
	}
	if (Input::IsKeyDown(DIK_Z))
	{
		Model::SetAnimFrame(hModel_, 180, 220, 1.0f);

	}

	if (dead)
	{
		if (gloTime > 180 && gloTime < 220 )
		{
			transFafro_.scale_.x -= 0.1f;
			transFafro_.scale_.y -= 0.1f;
			transFafro_.scale_.z -= 0.1f;
		}
		else if (gloTime > 220) {
			KillMe();
		}
		OutputDebugString("gloTime = ");
		Debug::Log(gloTime, true);

	}

	transform_.position_ = transFafro_.position_;
	gloTime++;
}

//描画
void Fafro::Draw()
{
	Model::SetTransform(hModel_, transFafro_);
	Model::Draw(hModel_);

}

//開放
void Fafro::Release()
{
}

void Fafro::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack")
	{
		dead = true;
		gloTime = 0;
		Model::SetAnimFrame(hModel_, 150, 170, 1.0f);
		
	}
}