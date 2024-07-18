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

    void CreateScores(int count);//�X�R�A�\����ݒu���鐔
    void CreateTimers(int count);//�^�C�}�[�\����ݒu���鐔
    void CreateJewels(int count);//�莝���̕�΂���ݒu���鐔


    void SetScorePosition(int index, int x, int y);//�Z�Ԗڂ̃X�R�A���ǂ��ɒu����
    void SetScoreValue(int index, int value);//�Z�Ԗڂ̃X�R�A�͉���\�����邩
    void CalcScoreValue(int index);//�Z�Ԗڂ̃X�R�A�̓Q�[�����̃X�R�A��\��
    bool IsCountEnd(int index);     //�Z�Ԗڂ̃X�R�A�͐����I�������

    void SetTimerPosition(int index, int x, int y);//�Z�Ԗڂ̃^�C�}�[�͂ǂ��ɒu���̂�
    void SetTimerLimit(int index, int limit);//�Z�Ԗڂ̃^�C�}�[�͉��b�ɐݒ肳���̂�
    void TimerStart(int index);
    bool IsFinished(int index);  //�^�C�}�[���I��������ǂ���

    void SetJewelPosition(int index, int x, int y);//�Z�Ԗڂ̎莝���̕�΂͂ǂ��ɒu���̂�
    void SetJewelValue(int index, int value);//�Z�Ԗڂ̕�΂͉���\������̂�

    void ScoreCountStart(int index);
    void ScoreCountStop(int index);
    void SetScoreIncrementStep(int index, int step);

    void HideScore() { displayScore = false; }
    void HideTimer() { displayTimer = false; }
    void HideJewel() { displayJewel = false; }
};