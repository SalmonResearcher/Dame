#include "StageSelectScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

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

	for (int l = 0; l < MAX_STAGE; l++)
	{
		num = std::to_string(l+1);

		//Stage1、Stage2、Stage3を呼ぶ
		hStage_[l] = Model::Load(name+num+ext);
		assert(hStage_[l] >= 0);
	}

	hSkysphere = Model::Load("SkySphere_Test.fbx");
	assert(hSkysphere >= 0);

	trStage1.scale_ = { 0.6f,0.6f,0.6f };
	trStage2.scale_ = { 0.6f,0.6f,0.6f };
	trStage3.scale_ = { 0.4f,0.4f,0.4f };

	trStage1.position_ = { 0,0,0 };
	trStage2.position_ = { 8,0,0 };
	trStage3.position_ = { 16,0,0 };


}

//更新
void StageSelectScene::Update()
{
	if (Input::IsKey(DIK_A))
	{

	}

	sinwave = sin(yMoveTime)/15;

	trStage1.position_.y = sinwave;
	trStage2.position_.y = sinwave;
	trStage3.position_.y = sinwave;

	trStage1.rotate_.y = timer / 2;
	trStage2.rotate_.y = timer / 2;
	trStage3.rotate_.y = timer / 2;


	yMoveTime += 0.05f;
	timer++;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

//描画
void StageSelectScene::Draw()
{
	//ここもforでできそうじゃないかな
	Model::SetTransform(hStage_[0], trStage1);
	Model::SetTransform(hStage_[1], trStage2);
	Model::SetTransform(hStage_[2], trStage3);

	for (int l = 0; l < MAX_STAGE; l++)
	{
		Model::Draw(hStage_[l]);
	}

}

//開放
void StageSelectScene::Release()
{
}
