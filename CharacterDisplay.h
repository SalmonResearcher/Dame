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

    void CreateScores(int count);//スコア表示を設置する数
    void CreateTimers(int count);//タイマー表示を設置する数
    void CreateJewels(int count);//手持ちの宝石をを設置する数


    void SetScorePosition(int index, int x, int y);//〇番目のスコアをどこに置くか
    void SetScoreValue(int index, int value);//〇番目のスコアは何を表示するか
    void CalcScoreValue(int index);//〇番目のスコアはゲーム中のスコアを表示
    bool IsCountEnd(int index);     //〇番目のスコアは数え終わったか

    void SetTimerPosition(int index, int x, int y);//〇番目のタイマーはどこに置くのか
    void SetTimerLimit(int index, int limit);//〇番目のタイマーは何秒に設定されるのか
    void TimerStart(int index);
    bool IsFinished(int index);  //タイマーが終わったかどうか

    void SetJewelPosition(int index, int x, int y);//〇番目の手持ちの宝石はどこに置くのか
    void SetJewelValue(int index, int value);//〇番目の宝石は何を表示するのか

    void ScoreCountStart(int index);
    void ScoreCountStop(int index);
    void SetScoreIncrementStep(int index, int step);

    void HideScore() { displayScore = false; }
    void HideTimer() { displayTimer = false; }
    void HideJewel() { displayJewel = false; }
};