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

    /*VFX�̒萔����*/
    const XMFLOAT3 PARTICLE_POSITION_RND = XMFLOAT3(0.8f, 0.0f, 0.8f);
    const XMFLOAT3 PARTICLE_DIRECTION = XMFLOAT3(0.0f, 1.0f, 0.0f);
    const XMFLOAT3 PARTICLE_DIRECTION_RND = XMFLOAT3(10.0f, 10.0f, 10.0f);
    const XMFLOAT2 PARTICLE_SIZE = XMFLOAT2(1.5f, 1.5f);
    const XMFLOAT2 PARTICLE_SCALE = XMFLOAT2(0.99f, 0.99f);
    const int PARTICLE_LIFETIME = 110;
    const float PARTICLE_SPEED = 0.05f;
    const XMFLOAT3 PARTICLE_SPIN = XMFLOAT3(0.0f, 0.0f, 0.1f);
    const float PARTICLE_GRAVITY = 0.0f;
    const float PARTICLE_DELAY = 0.0f;

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

    // �C�[�W���O�֐�
    float easeInOutCubic(float x) 
    {
        if (x < 0.5) {
            return 4.0f * pow(x, 3);
        }
        else {
            return 1.0f - pow(-2 * x + 2, 3) / 2.0f;
        }
    }

    //��L���X�g�p�X�e�[�W
    int SetStageHandle();

    //�����ɓ�������
    void OnCollision(GameObject* pTarget) override;

    void CreateVFX();

    void DestroyVFX();
};
