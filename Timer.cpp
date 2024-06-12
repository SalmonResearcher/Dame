#include "Timer.h"

static const int FPS = 60;

Timer::Timer(GameObject* parent)
	:GameObject(parent, "CharacterDisplay"),
	frame(1200), active(false)
{
	num = new Text;
	num->Initialize("time_number.png", 50, 100, 10);
}

Timer::~Timer()
{
	delete num;
}

void Timer::Initialize()
{
	frame = 0;
	active = false;
}

void Timer::Update()
{
	if (active) {
		if (frame > 0) {
			frame--;
		}
	}
}

void Timer::Draw()
{
	int sec = frame / FPS;

	// 2����0���߂̃t�H�[�}�b�g�w��q���g�p���ĕ�����𐶐�
	char buffer[3]; // ������+1���̔z��T�C�Y
	snprintf(buffer, sizeof(buffer), "%02d", sec);
	std::string result = buffer;

	num->Draw(posX_, posY_, result.c_str(), true);

}

void Timer::Release()
{
}

void Timer::SetLimit(float seconds)
{
	frame = (int)(seconds * FPS);
}

void Timer::Start()
{
	active = true;
}

void Timer::Stop()
{
	active = false;
}

bool Timer::IsFinished()
{
	return (frame == 0);
}
