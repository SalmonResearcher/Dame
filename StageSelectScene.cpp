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

		hStage_[l] = Model::Load(name+num+ext);
		assert(hStage_[l] >= 0);
	}

	hSkysphere = Model::Load("SkySphere_Test.fbx");
	assert(hSkysphere >= 0);

	trStage1.scale_ = { 0.7f,0.7f,0.7f };
	trStage2.scale_ = { 0.8f,0.8f,0.8f };
	trStage3.scale_ = { 0.4f,0.4f,0.4f };


}

//更新
void StageSelectScene::Update()
{
	sinwave = sin(timer)/5;

	trStage1.rotate_.y = timer / 2;
	trStage2.rotate_.y = timer / 2;
	trStage3.rotate_.y = timer / 2;

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
	Model::SetTransform(hStage_[1], trStage1);
	Model::SetTransform(hStage_[2], trStage2);
	Model::SetTransform(hStage_[3], trStage3);

	for (int l = 0; l < MAX_STAGE; l++)
	{
		Model::Draw(hStage_[l]);
	}

}

//開放
void StageSelectScene::Release()
{
}
