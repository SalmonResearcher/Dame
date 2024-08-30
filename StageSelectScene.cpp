#include "StageSelectScene.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"
#include "Global.h"

namespace {
	XMFLOAT3 cameraPos;
	float moveX;

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
	hBGM_ = Audio::Load("SE/SelectScene.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, Global::MUSIC_VOLUME);

	/*
	const char* modelName[] = { "MiniStage1.fbx" };
	for (int l = 0; l < MAX_STAGE; l++)
	{
		num = std::to_string(l+1);

		hStage_[l] = Model::Load(modelName[l]);
		assert(hStage_[l] >= 0);

		trStage[l].scale_ = STAGE_SCALE;
	}*/
	for (int l = 0; l < 2; l++)
	{
		hImage_[l] = Model::Load("Arrow.png");
	}

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
				pSceneManager->ChangeScene(SCENE_ID_TEST);

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

		trStage[l].rotate_.y = timer / STAGE_ROTATE_SPEED;
	}


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
	
	Image::SetTransform(hImage_[0], trImage_[0]);
	Image::Draw(hImage_[0]);
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
