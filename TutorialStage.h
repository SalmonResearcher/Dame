#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TutorialStage : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hModel2_;

    Transform transSky_;


    float signY_;
    float jewelY_;
    bool spawned_ = false;

    // �萔�̒�`
    const XMFLOAT3 INIT_POSITION = { 500, -6, 0 };

    const float SIGN_POSITION_Z[4] = { 7.0f, 25.0f, 35.0f, 45.0f };
    const float JEWEL_POSITION_Z = 20.0f;
    const float PLAYER_POSITION_Y_THRESHOLD = -15.0f;
    const float PLAYER_POSITION_Z_THRESHOLD = 65.0f;

    //UI���
    const int JEWEL_POSITION_X = 1150;
    const int JEWEL_POSITION_Y = 110;
    const int SCORE_POSITION_X = 950;
    const int SCORE_POSITION_Y = 45;
    const int TIMER_POSITION_X = 600;
    const int TIMER_POSITION_Y = 45;

    // �X�R�A�ƃ^�C�}�[�̏����l
    const int INITIAL_SCORE = 0;
    const int INITIAL_TIMER_LIMIT = 0;

    // �W���G���{�b�N�X�̈ʒu
    const XMFLOAT3 JEWEL_BOX_POSITION = { 0, -7, 55 };

    //�Ŕ̔��]
    const XMFLOAT3 DEFAULT_SIGN_ROTATION = { 0, 180, 0 };

public:
    //�R���X�g���N�^
    TutorialStage(GameObject* parent);

    //�f�X�g���N�^
    ~TutorialStage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���ԍ���Ԃ�
    int GetModelHandle() { return hModel_; }
};