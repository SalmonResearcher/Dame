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

//�R���X�g���N�^
Tutorial::Tutorial(GameObject* parent)
	: GameObject(parent, "Tutorial"), hBGM_(-1)
{
}

//������
void Tutorial::Initialize()
{
	hBGM_ = Audio::Load("SE/Tutorial.wav", true);
	assert(hBGM_ >= 0);
	Audio::Play(hBGM_, false, 1.0f, Global::MUSIC_VOLUME);

	pPlayer_ = Instantiate<Player>(this);
	pStage_ = Instantiate<TutorialStage>(this);

}

//�X�V
void Tutorial::Update()
{
}

//�`��
void Tutorial::Draw()
{
}

//�J��
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