#pragma once
#include "Engine/GameObject.h"
class EnemyAttack : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMFLOAT3 pos_;
    int time_;

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

    void SetAttackPosition(XMFLOAT3 _pos) { pos_ = _pos; }

    void SetTime(int _time) { time_ = _time; };

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

};