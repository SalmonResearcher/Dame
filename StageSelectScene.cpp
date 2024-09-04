#include "StageSelectScene.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"
#include "Global.h"

namespace {
	XMFLOAT3 cameraPos;
	float moveX;
	float moveXImage;

	int hSkysphere;
	Transform trSky;

	std::string name = "MiniStage";
	std::string num;
	std::string ext = ".fbx";

	//ステージの移動量
	float moveStage = 0.25f;

	//回転用の時間
	float timer;

	//縦揺れ量
	float yTime = 0.06f;

	//最大
	const XMFLOAT3 IMAGE_SCALE = { 0.3,0.3,0.3 };
	const int IMAGE_MAX_ALPHA = 192;		//画像の最大不透明度
	const int IMAGE_ROTATE = 180;			//画像の回転
	const float IMAGE_POSITiON = 0.8f;		//画像の位置
	const int IMAGE_WAVE_VEL = 100;			//画像の横揺れのつよさ
}

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene"),hBGM_(-1)
{
	//ステージプレビューモデル変数の初期化
	for (int i = 0; i < MAX_STAGE; i++)
	{
		hStage_[i] = -1;
	}
}

//初期化
void StageSelectScene::Initialize()
{
	hBGM_ = Audio::Load("Sounds/BGM/SelectScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, Global::MUSIC_VOLUME);

	for (int l = 0; l < MAX_IMAGE; l++)
	{
		hImage_[l] = Image::Load("Arrow.png");
		assert(hImage_[l] >= 0);

		trImage_[l].scale_ = IMAGE_SCALE;

	}
	trImage_[IMAGE_1].position_.x= IMAGE_POSITiON;
	trImage_[IMAGE_2].position_.x = -IMAGE_POSITiON;

	trImage_[IMAGE_1].rotate_.z = IMAGE_ROTATE;

	hStage_[STAGE1] = Model::Load("TutorialChar.fbx");
	hStage_[STAGE2] = Model::Load("MiniStage1.fbx");

	trStage[STAGE1].position_ = { 0,0,0 };
	trStage[STAGE2].position_ = { 8,0,0 };

	trStage[STAGE1].scale_ = STAGE_SCALE;
	trStage[STAGE2].scale_ = STAGE_SCALE;

	cameraPos = {0,2,-5 };
}

//更新
void StageSelectScene::Update()
{
	if (Input::IsKeyDown(DIK_A) && selectCount > 0)
	{
		selectCount--;
		isStageStop = false;
		moveX = -moveStage;
	}

	if (Input::IsKeyDown(DIK_D) && selectCount < MAX_STAGE - 1)
	{
		selectCount++;
		isStageStop = false;
		moveX = moveStage;
	}

	switch (selectCount)
	{
	case STAGE1:
		alImage_[IMAGE_1] = IMAGE_MAX_ALPHA;
		alImage_[IMAGE_2] = 0;

		cameraPos.x += moveX;
		if (cameraPos.x <= trStage[STAGE1].position_.x){
			moveX = 0;
			isStageStop = true;
		}
		StageScaling(&trStage[STAGE1], true);
		StageScaling(&trStage[STAGE2], false);

		if (Input::IsKeyDown(DIK_SPACE))
		{
			cameraPos.x = trStage[STAGE1].position_.x; 
			if (isStageStop && Input::IsKeyDown(DIK_SPACE))
			{
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_TUTORIAL);
			}
		}
		break;

	case STAGE2:
		alImage_[IMAGE_2] = IMAGE_MAX_ALPHA;
		alImage_[IMAGE_1] = 0;

		if (cameraPos.x < trStage[STAGE2].position_.x ||
			cameraPos.x > trStage[STAGE2].position_.x)
		{
			cameraPos.x += moveX;
		}
		else
		{
			moveX = 0.0f; 
			isStageStop = true;
		}

		StageScaling(&trStage[STAGE1], false);
		StageScaling(&trStage[STAGE2], true);

		if (Input::IsKeyDown(DIK_SPACE))
		{
			cameraPos.x = trStage[STAGE2].position_.x;
			if (isStageStop && Input::IsKeyDown(DIK_SPACE))
			{
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_PLAY);

			}
		}
		break;
	}

	Camera::SetPosition(cameraPos);
	Camera::SetTarget({ cameraPos.x,0,0 });

	sinwave = sin(yMoveTime)/WAVE_VELOCITY;
	for (int l = STAGE1; l < MAX_STAGE; l++)
	{
		trStage[l].position_.y = sinwave;
		moveXImage = sinwave / IMAGE_WAVE_VEL;

		trStage[l].rotate_.y = timer / STAGE_ROTATE_SPEED;
	}

	for (int l = 0; l < MAX_IMAGE; l++)
	{
	}
	trImage_[IMAGE_1].position_.x += moveXImage;
	trImage_[IMAGE_2].position_.x -= moveXImage;


	yMoveTime += yTime;
	timer++;
}

//描画
void StageSelectScene::Draw()
{

	//ここもforでできそうじゃないかな
	//高野産のおかげで回せるようになった！ありがとう
	for (int i = 0; i < MAX_STAGE; i++)
	{
		Model::SetTransform(hStage_[i], trStage[i]);
	}

	for (int l = 0; l < MAX_STAGE; l++)
	{
		Model::Draw(hStage_[l]);
	}
	
	for (int l = 0; l < MAX_IMAGE; l++)
	{
		Image::SetAlpha(hImage_[l], alImage_[l]);
		Image::SetTransform(hImage_[l], trImage_[l]);
		Image::Draw(hImage_[l]);

	}
	//for (int i = 0; i < 2; i++)
	//{
	//	Image::SetTransform(hImage_[i], trImage_[i]);
	//	Image::Draw(hImage_[i]);
	//}

}

//開放
void StageSelectScene::Release()
{
	
}

void StageSelectScene::StageScaling(Transform* stage_, bool big)
{
	StageScaling(stage_, big, 1);
}

void StageSelectScene::StageScaling(Transform* stage_, bool big, float rate)
{
	if (big)
	{
		if (stage_->scale_.x <= STAGE_BIG.x * rate)
		{
			stage_->scale_.x += SCALE_UP_SPEED;
			stage_->scale_.y += SCALE_UP_SPEED;
			stage_->scale_.z += SCALE_UP_SPEED;
		}
	}
	else
	{
		if (stage_->scale_.x >= STAGE_SCALE.x *rate)
		{
			stage_->scale_.x -= SCALE_UP_SPEED;
			stage_->scale_.y -= SCALE_UP_SPEED;
			stage_->scale_.z -= SCALE_UP_SPEED;
		}
	}
}
