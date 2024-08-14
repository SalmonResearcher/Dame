#pragma once
#include "Engine/GameObject.h"
#include "Engine/SphereCollider.h"

#include "Player.h"
#include "Engine/VFX.h"

class SphereCollider;

enum STATE {
    MOVE,
    ATTACK,
    DEATH,
    MAX
};

class Enemy : public GameObject
{
    SphereCollider* pSpher;
    Player* pPlayer;

    int hModel_;    //���f���ԍ�
    int hDeathSound_;    //�T�E���h�ԍ�
    int hHitSound_; //�q�b�g

    int hStage_;    //�X�e�[�W���f��
    int hPlayer_;   //�v���C���[�̃��f���ԍ�

    int hEmit_; //�G�t�F�N�g�ԍ�
    bool stopEmit_;

    int killed_by_Jewel;

    STATE states;
    int curState;   //1f�O�̏��
    bool isChange;  //�X�e�[�g��ύX���邩�ǂ����i�A�j���[�V�����̐ݒ�̍ۂɎg�p�j

    XMVECTOR vPosition_;    //���g�̈ʒu�x�N�g��
    XMFLOAT3 target_;       //�v���C���[�̈ʒu
    XMVECTOR vTarget_;      //�v���C���[�̈ʒu�x�N�g��
    XMVECTOR direction_;    //�v���C���[�ƓG�̕����x�N�g��
    float toPlayerdir;      //�v���C���[�܂ł̒�������

    int waitTime_ = 0;

    bool isDead = false;    //����ł��邩�ǂ���
    bool counted;           //�|���ꂽ�J�E���g���ꂽ���ǂ���

    float volume;

    EmitterData vfx;

    bool isNearPlayer_;//�v���C���[���߂��ɂ��邩
    bool isAttackEnd_; //�U�����I�������

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

    void ChangeAnime(STATE state);

    //�����ɉ����ĉ��ʂ�ς���
    float SoundDistance(float distance,float falloff);

    //Float�̃����_���Ȓl�𐶐����܂�
    float GenerateRandomFloat(float min, float max);

    //�G�t�F�N�g
    void CreateVFX(int num);

    //�G�t�F�N�g�̏���
    void DestroyVFX();

    bool GetEnemyDeath() { return isDead; };
    bool IsNearPlayer() { return  isNearPlayer_; };
    bool IsAttackEnd() { return isAttackEnd_; };

};