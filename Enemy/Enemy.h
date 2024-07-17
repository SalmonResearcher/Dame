#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SphereCollider.h"

#include "../Player.h"

class SphereCollider;

enum STATE {
    MOVE,
    ATTACK,
    DEATH,
    MAX
};

struct {
    int startFrame;
    int endFrame;
    float animeSpeed;
};

class Enemy : public GameObject
{
    SphereCollider* pSpher;
    Player* pPlayer;

    int hModel_;    //���f���ԍ�
    int hSound_;    //�T�E���h�ԍ�
    int hSoundHit_; //�q�b�g

    int hStage_;    //�X�e�[�W���f��
    int hPlayer_;   //�v���C���[�̃��f���ԍ�

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
    int killcount;

    bool isDead = false;
    bool counted;

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

    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    int GetModelHandle() { return hModel_; }

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    void ChasePlayer(XMFLOAT3& target_, float speed);

    void Attack();

    void Death();
    void JewelDeath();

    void ChangeAnime(STATE state);

    
};