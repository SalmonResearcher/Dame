#include "Tutorial.h"
#include "Global.h"

#include "Player.h"
#include "TutorialStage.h"
#include "Jewel.h"
#include "JewelBox.h"
#include "CharacterDisplay.h"


#include "Engine/SceneManager.h"
#include "Engine/Audio.h"

namespace {
}

//コンストラクタ
Tutorial::Tutorial(GameObject* parent)
	: GameObject(parent, "Tutorial"), hBGM_(-1)
{
}

//初期化
void Tutorial::Initialize()
{
	hBGM_ = Audio::Load("SE/Tutorial.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, Global::MUSIC_VOLUME);

	pPlayer_ = Instantiate<Player>(this);
	pStage_ = Instantiate<TutorialStage>(this);

}

//更新
void Tutorial::Update()
{
}

//描画
void Tutorial::Draw()
{
}

//開放
void Tutorial::Release()
{
}

void Tutorial::SoundPlay(int  handle, int interval)
{
	if (soundtimer % interval == 0) {
		Audio::Play(handle, true);
	}
	soundtimer++;
}