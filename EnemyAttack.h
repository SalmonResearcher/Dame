#pragma once
#include "Engine/GameObject.h"
class EnemyAttack : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMFLOAT3 move_ = { 0,0,0 };
    int time;

public:
    //�R���X�g���N�^
    EnemyAttack(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyAttack();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetMove(XMFLOAT3 move) { move_ = move; }

    void SetTime(int _time) { time = _time; };
    void SetTime() { time = -1; };

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

};