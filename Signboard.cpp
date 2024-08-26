#include "Signboard.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Audio.h"
#include "TutorialStage.h"
#include "Player.h"

namespace {
	int startAnimation = 0;
	int endAnimation = 60;
	float animSpeed = 1.0f;

	XMFLOAT3 colliderPosition = { 0.0f,0.0f,0.0f };
	float colliderScale = 1.25f;

}


//コンストラクタ
SignBoard::SignBoard(GameObject* parent)
    :GameObject(parent, "SignBoard"),animTime_(0), hModel_(-1), stopEmit_(false),isAnimEnd_(true)
{

    SphereCollider* collision = new SphereCollider(colliderPosition,colliderScale);
    AddCollider(collision);
}

//デストラクタ
SignBoard::~SignBoard()
{
}

//初期化
void SignBoard::Initialize()
{

    hModel_ = Model::Load("Sign.fbx");
    assert(hModel_ >= 0);

	hSound_ = Audio::Load();

    hStage_ = SetStageHandle();


}

//更新
void SignBoard::Update()
{
	RayCastData data;
	data.start = { transform_.position_ };   //レイの発射位置
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
	Model::RayCast(hStage_, &data); //レイを発射

	if (data.hit)
	{
		transform_.position_.y = -data.dist;
	}


	if (animTime_ != 0)
	{
		isAnimEnd_ = false;
		animTime_--;
	}
	else if (animTime_ == 0)
	{
		isAnimEnd_ = true;
		Model::SetAnimFrame(hModel_, startAnimation, startAnimation, animSpeed);
	}
}

//描画
void SignBoard::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void SignBoard::Release()
{
}

int SignBoard::SetStageHandle()
{
    if ((FindObject("TutorialStage")) != nullptr)
    {
        return ((TutorialStage*)FindObject("TutorialStage"))->GetModelHandle();
    }
}

void SignBoard::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Attack" && isAnimEnd_)
	{
		Model::SetAnimFrame(hModel_, startAnimation, endAnimation, animSpeed);
		CreateVFX(HIT);
		animTime_ = endAnimation;
	}    
	
	if (pTarget->GetObjectName() == "JewelBullet" && isAnimEnd_)
	{
		Model::SetAnimFrame(hModel_, startAnimation, endAnimation, animSpeed);
		CreateVFX(JEWEL);
		animTime_ = endAnimation;
	}

}

void SignBoard::CreateVFX(STATEVFX svfx)
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

	default:
		break;
	}
}


void SignBoard::DestroyVFX()
{
    stopEmit_ = true;
}

