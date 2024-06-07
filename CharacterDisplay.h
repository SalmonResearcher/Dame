// CharacterDisplay.h
#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include <vector>

class Score;
class Timer;
class JewelNumber;

class CharacterDisplay : public GameObject
{
private:
    std::vector<Score*> scores;
    std::vector<Timer*> timers;
    std::vector<JewelNumber*> jewels;

    bool displayScore, displayTimer, displayJewel;

public:
    CharacterDisplay(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void SetScoreValue(int index, int value);
    void SetScorePosition(intindex, int x, int y);

    void SetTimer(int index, int limit);
    void SetTimerPosition(int index, int x, int y);
    void SetJewelValue(int index, int value);
    void SetJewelPosition(int index, int x, int y);

    void CreateScores(int count);
    void CreateTimers(int count);
    void CreateJewels(int count);

    void HideScore() { displayScore = false; }
    void HideTimer() { displayTimer = false; }
    void HideJewel() { displayJewel = false; }
};