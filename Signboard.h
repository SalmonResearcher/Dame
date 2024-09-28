#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

class SignBoard :
    public GameObject
{
    enum STATEVFX {
        HIT,
        JEWEL
    };

    int hModel_;    //���f���ԍ�
    int hStage_;
    int animTime_;
    bool isAnimEnd_;    //animation���I�������
    int hSound_;

    int hEmit_;//VFX�̔ԍ�
    bool stopEmit_;
    EmitterData vfx_;

    //�A�j���[�V�����萔
    const int START_ANIM = 0;
    const int END_ANIM = 60;
    const float ANIM_SPEED = 1.0f;

    //�R���C�_�[
    XMFLOAT3 colliderPosition = { 0.0f,1.0f,0.0f };
    const float COLLIDER_SCARE = 1.25f;

        /*VFX�̒萔�B*/
    // �ʒu�I�t�Z�b�g�̒萔
    static constexpr float HIT_EFFECT_OFFSET_Y = 0.7f;
    // �G�t�F�N�g�̃T�C�Y
    static constexpr XMFLOAT2 EFFECT_SIZE_LARGE = XMFLOAT2(4, 4);
    // �G�t�F�N�g�̃X�P�[��
    static constexpr XMFLOAT2 EFFECT_SCALE_DEFAULT = XMFLOAT2(1.2, 1.2);
    // ���C�t�^�C��
    static constexpr int LIFETIME_SHORT = 5;
    // ��]��
    static constexpr XMFLOAT3 EFFECT_SPIN = XMFLOAT3(0, 0, 15.0f);



public:
    //�R���X�g���N�^
    SignBoard(GameObject* parent);

    //�f�X�g���N�^
    ~SignBoard();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���C�L���X�g�p�X�e�[�W
    int SetStageHandle();

    //�����ɓ�������
    void OnCollision(GameObject* pTarget) override;

    void CreateVFX(STATEVFX svfx);

    void DestroyVFX();
};
