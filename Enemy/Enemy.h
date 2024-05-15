#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SphereCollider.h"

#include "../Player.h"

enum STATE {
    MOVE,
    ATTACK,
    DEATH,
    MAX
};


class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�
    SphereCollider* pSpher = new SphereCollider(XMFLOAT3(0, 0.8f, 0), 1.25f);


    int hStage_;
    int hPlayer_;

    STATE states;
    int curState;//1f�O�̏��
    bool isChange;//�X�e�[�g��ύX���邩�ǂ����i�A�j���[�V�����̐ݒ�̍ۂɎg�p�j

    Transform tEnemy_;

    XMVECTOR vPosition_; //���g�̂���
    XMFLOAT3 target_;
    XMVECTOR vTarget_;
    XMVECTOR direction_;
    float toPlayerdir;  //�v���C���[�܂ł̒�������

    XMFLOAT3 bonepos;
    float moveY = 0.0f;
    float speed = 0.5f;

    int startFrame;
    int endFrame;
    float animeSpeed;
    int waitTime = 0;

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

    void AttackPlayer();

    void Death();

    void ChangeAnime(STATE state);

};