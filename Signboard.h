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
