#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

#include "Player.h"
#include "Engine/VFX.h"


class SphereCollider;
class StateManager;

enum STATEVFX {
    HIT,
    JEWEL,
    DEATH
};

class Enemy : public GameObject
{
    SphereCollider* pSpher_;
    Player* pPlayer_;
    StateManager* pStateManager_;

    int hModel_;    //���f���ԍ�
    int hDeathSound_;    //�T�E���h�ԍ�
    int hHitSound_; //�q�b�g�������̉�

    int hStage_;    //�X�e�[�W���f��
    int hPlayer_;   //�v���C���[�̃��f���ԍ�

    int hEmit_;     //�G�t�F�N�g�ԍ�
    bool stopEmit_; //�G�t�F�N�g���~�߂�

    int killedByJewel_;

    XMVECTOR vPosition_;    //���g�̈ʒu�x�N�g��
    XMFLOAT3 target_;       //�v���C���[�̈ʒu
    XMVECTOR vTarget_;      //�v���C���[�̈ʒu�x�N�g��
    XMVECTOR direction_;    //�v���C���[�ƓG�̕����x�N�g��
    float toPlayerdir_;      //�v���C���[�܂ł̒�������

    int waitTime_ = 0;

    //����ł��邩�ǂ���
    bool isDead_ = false;

    //�|���ꂽ�J�E���g���ꂽ���ǂ���
    bool counted_;           

    float volume_;

    EmitterData vfx_;

    //�v���C���[���߂��ɂ��邩
    bool isNearPlayer_;

    //�U�����I�������
    bool isAttackEnd_; 
    
    /*VFX�̒萔�B*/
    // �ʒu�I�t�Z�b�g�̒萔
    static constexpr float HIT_EFFECT_OFFSET_Y = 0.7f;
    // �G�t�F�N�g�̃T�C�Y
    static constexpr XMFLOAT2 EFFECT_SIZE_LARGE = XMFLOAT2(4, 4);
    static constexpr XMFLOAT2 EFFECT_SIZE_SMALL = XMFLOAT2(1, 1);
    // �G�t�F�N�g�̃X�P�[��
    static constexpr XMFLOAT2 EFFECT_SCALE_DEFAULT = XMFLOAT2(1.2, 1.2);
    static constexpr XMFLOAT2 EFFECT_SCALE_SMALL = XMFLOAT2(0.99, 0.99);
    // ���C�t�^�C��
    static constexpr int LIFETIME_SHORT = 5;
    static constexpr int LIFETIME_LONG = 25;
    // ���̑��̒萔
    static constexpr float EFFECT_SPEED_DEATH = 0.4f;
    static constexpr float EFFECT_GRAVITY = 0.02f;
    static constexpr XMFLOAT3 EFFECT_SPIN = XMFLOAT3(0, 0, 15.0f);
    static constexpr XMFLOAT3 POSITION_RND_DEATH = XMFLOAT3(0.8f, 0, 0.8f);
    static constexpr XMFLOAT3 DIRECTION_RND_DEATH = XMFLOAT3(15, 15, 15);
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //State
    void Walk();
    void Attack();
    void AttackCollision();
    void Dead();


    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    int GetModelHandle() { return hModel_; }

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    void ChasePlayer(XMFLOAT3& target_, float speed);

    void JewelDeath();//��΂ɂ���Ă��ꂽ

    //�����ɉ����ĉ��ʂ�ς���
    float SoundDistance(float distance,float falloff);

    //Float�̃����_���Ȓl�𐶐����܂�
    float GenerateRandomFloat(float min, float max);

    //�G�t�F�N�g
    void CreateVFX(STATEVFX svfx);

    //�G�t�F�N�g�̏���
    void DestroyVFX();

    bool GetEnemyDeath() { return isDead_; };
    bool IsNearPlayer() { return  isNearPlayer_; };
    bool IsAttackEnd() { return isAttackEnd_; };
    void SetAttackTime();
    void SetDeadTime();
};