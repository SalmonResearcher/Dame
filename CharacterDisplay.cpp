// CharacterDisplay.cpp
#include "CharacterDisplay.h"
#include "Score.h"
#include "Timer.h"
#include "JewelNumber.h"
#include "Engine/Debug.h"

CharacterDisplay::CharacterDisplay(GameObject* parent)
    : GameObject(parent, "CharacterDisplay"),
    displayScore(true), displayTimer(true), displayJewel(true)
{
}

void CharacterDisplay::Initialize()
{
}

void CharacterDisplay::Update()
{
}

void CharacterDisplay::Draw()
{
    if (displayScore) {
        for (size_t i = 0; i < scores.size(); ++i) {
            scores[i]->Draw();
        }
    }
    if (displayTimer) {
        for (size_t i = 0; i < timers.size(); ++i) {
            timers[i]->Draw();
        }
    }
    if (displayJewel) {
        for (size_t i = 0; i < jewels.size(); ++i) {
            jewels[i]->Draw();
        }
    }
}

bool CharacterDisplay::IsCountEnd(int index)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        return scores[index]->IsCountEnd();
    }
}


void CharacterDisplay::Release()
{
}

void CharacterDisplay::SetScorePosition(int index, int x, int y)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->SetDisplayPosition(x,y);
    }
}

void CharacterDisplay::SetScoreValue(int index, int value)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->SetScore(value);
    }
}

void CharacterDisplay::CalcScoreValue(int index)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->ScoreCaluc();
    }
}

void CharacterDisplay::SetTimerPosition(int index, int x, int y)
{
    if (index >= 0 && index < static_cast<int>(timers.size())) {
        timers[index]->SetTimerPosition(x, y);
    }
}

void CharacterDisplay::SetTimerLimit(int index, int limit)
{
    if (index >= 0 && index < static_cast<int>(timers.size())) {
        timers[index]->SetLimit(limit);
    }
}

void CharacterDisplay::SetJewelPosition(int index, int x, int y)
{
    if (index >= 0 && index < static_cast<int>(jewels.size())) {
        jewels[index]->SetJewelPosition(x, y);
    }
}

void CharacterDisplay::SetJewelValue(int index, int value)
{
    if (index >= 0 && index < static_cast<int>(jewels.size())) {
        jewels[index]->SetJewelNumber(value);
    }
}

void CharacterDisplay::CreateScores(int count)
{
    for (int i = 0; i < count; ++i) {
        scores.push_back(Instantiate<Score>(this));
    }
}

void CharacterDisplay::CreateTimers(int count)
{
    for (int i = 0; i < count; ++i) {
        auto timer = Instantiate<Timer>(this);
        timer->SetLimit(0); // タイマー一応初期化
        timers.push_back(timer);
    }
}

void CharacterDisplay::CreateJewels(int count)
{
    for (int i = 0; i < count; ++i) {
        jewels.push_back(Instantiate<JewelNumber>(this));
    }
}

void CharacterDisplay::ScoreCountStart(int index)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->Start();
    }
}

void CharacterDisplay::ScoreCountStop(int index)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->Stop();
    }
}

void CharacterDisplay::SetScoreIncrementStep(int index, int step)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->SetIncrementSteps(step);
    }
}

void CharacterDisplay::InstantSyncScore(int index)
{
    if (index >= 0 && index < static_cast<int>(scores.size())) {
        scores[index]->InstantSyncScore();
    }

}

bool CharacterDisplay::IsFinished(int index) 
{
    if (index >= 0 && index < static_cast<int>(timers.size())) {
        return timers[index]->IsFinished();
    }
}

void CharacterDisplay::TimerStart(int index)
{
    if (index >= 0 && index < static_cast<int>(timers.size())) {
        timers[index]->Start();
    }
}
