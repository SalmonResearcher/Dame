#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

class Jewel :
    public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;
    int time_;
    float rotY = 0.0f;
    bool jewelRotate_;

    int hEmit_;//VFX�̔ԍ�
    bool stopEmit_;
    EmitterData vfx;


public:
    //�R���X�g���N�^
    Jewel(GameObject* parent);

    //�f�X�g���N�^
    ~Jewel();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�C�[�W���O�֐�
    float easeInOutCubic(float x) {
        return x < 0.5 ? 4 * pow(x, 3) : 1 - pow(-2 * x + 2, 3) / 2;
    }

    //��L���X�g�p�X�e�[�W
    int SetStageHandle();

    //�����ɓ�������
    void OnCollision(GameObject* pTarget) override;

    void CreateVFX();

    void DestroyVFX();
};
