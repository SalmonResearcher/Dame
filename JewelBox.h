#pragma once
#include "Engine/GameObject.h"

class Player;

//�[�i�����Ǘ�����N���X
class JewelBox : public GameObject
{
    int hModel_;    //���f���ԍ�

    int jewel_ = 0;
    int score_ = 0;

    int anim_Start;
    int anim_End;
    int anim_Speed;

public:
    //�R���X�g���N�^
    JewelBox(GameObject* parent);

    //�f�X�g���N�^
    ~JewelBox();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���ԍ���Ԃ�
    int GetModelHandle() { return hModel_; };

    void OnCollision(GameObject* pTarget);

    void AddScore(int _score) { score_ += _score; };

    int ReturnJewel() { return jewel_; };
    int GetKillScore() { return score_; };
    int SetStageHandle();
};