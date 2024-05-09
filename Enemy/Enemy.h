#pragma once
#include "../Engine/GameObject.h"
#include "../Player.h"

enum STATE{
    MOVE,
    ATTACK,
    DEATH,
    MAX
};


class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�

    int hStage_;
    int hPlayer_;

    STATE states;

    Transform transEnemy_;

    XMVECTOR vPosition_; //���g�̂���
    XMFLOAT3 target_;
    XMVECTOR vTarget_;
    XMVECTOR direction_;

    float moveY = 0.0f;
    float speed = 0.5f;

    int startFrame;
    int endFrame;
    float animeSpeed;
 
    bool isLive = true;

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

    void 
};