#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TutorialStage : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hModel2_;
    Transform transSky_;


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