#include "StageSelectScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"

//コンストラクタ
StageSelectScene::StageSelectScene(GameObject* parent)
	: GameObject(parent, "StageSelectScene")
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
	const char* modelName[] = { "MiniStage1.fbx","MiniStage2.fbx", "MiniStage3.fbx" };
	for (int l = 0; l < MAX_STAGE; l++)
	{
		num = std::to_string(l+1);

		//Stage1、Stage2、Stage3を呼ぶ
		hStage_[l] = Model::Load(modelName[l]);
		assert(hStage_[l] >= 0);

		trStage[l].scale_ = STAGE_SCALE;
	}

	hSkysphere = Model::Load("SkySphere.fbx");
	assert(hSkysphere >= 0);


	trStage[STAGE1].position_ = { 0,0,0 };
	trStage[STAGE2].position_ = { 8,0,0 };
	trStage[STAGE3].position_ = { 16,0,0 };

	cameraPos = {2,2,-5 };
}

//更新
void StageSelectScene::Update()
{
	if (Input::IsKeyDown(DIK_A) && selectCount > 0)
	{
		selectCount--;
		moveX = -0.25f;
	}

	if (Input::IsKeyDown(DIK_D) && selectCount < MAX_STAGE - 1)
	{
		selectCount++;
		moveX = 0.25f;
	}

	switch (selectCount){
	case 0:
		cameraPos.x += moveX;
		if (cameraPos.x <= trStage[STAGE1].position_.x + 2){
			moveX = 0;
		}
		StageScaling(&trStage[STAGE1], true);
		StageScaling(&trStage[STAGE2], false);
		StageScaling(&trStage[STAGE3], false);
		break;

	case 1:
		if (cameraPos.x < trStage[STAGE2].position_.x+2 ||
			cameraPos.x > trStage[STAGE2].position_.x+2)
		{
			cameraPos.x += moveX;
		}
		else moveX = 0.0f;

		StageScaling(&trStage[STAGE1], false);
		StageScaling(&trStage[STAGE2], true);
		StageScaling(&trStage[STAGE3], false);


		break;

	case 2:
		if (cameraPos.x < trStage[STAGE3].position_.x+2 || cameraPos.x > trStage[STAGE3].position_.x+2)
		{
			cameraPos.x += moveX;
		}
		else moveX = 0.0f;

		StageScaling(&trStage[STAGE1], false);
		StageScaling(&trStage[STAGE2], false);
		StageScaling(&trStage[STAGE3], true);

		if (Input::IsKeyDown(DIK_SPACE))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TEST);
		}

		break;
	}

	Camera::SetPosition(cameraPos);
	Camera::SetTarget({ cameraPos.x,0,0 });

	sinwave = sin(yMoveTime)/5;

	trStage[STAGE1].position_.y = sinwave;
	trStage[STAGE2].position_.y = sinwave;
	trStage[STAGE3].position_.y = sinwave;

	trStage[STAGE1].rotate_.y = timer / 3;
	trStage[STAGE2].rotate_.y = timer / 3;
	trStage[STAGE3].rotate_.y = timer / 3;

	yMoveTime += 0.06f;
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
			stage_->scale_.x += 0.03f;
			stage_->scale_.y += 0.03f;
			stage_->scale_.z += 0.03f;
		}
	}
	else
	{
		if (stage_->scale_.x >= STAGE_SCALE.x *rate)
		{
			stage_->scale_.x -= 0.05f;
			stage_->scale_.y -= 0.05f;
			stage_->scale_.z -= 0.05f;
		}
	}
}
