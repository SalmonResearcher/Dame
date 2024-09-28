#pragma once
#include "Engine/GameObject.h"
class Attack : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMFLOAT3 move_;

    int deleteTime_;

    XMFLOAT3 attackPos_;

    //���̐���ύX����ƍU�����肪�ł����Ȃ�
    const float ATTACK_SIZE = 0.8f;


public:
    //�R���X�g���N�^
    Attack(GameObject* parent);

    //�f�X�g���N�^
    ~Attack();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetMove(XMFLOAT3 move) { move_ = move; }

    void SetDeleteTime(int _time) { deleteTime_ = _time; };

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //�U������̕������v���C���[�̕���������炤
    void AttackDirection(XMVECTOR _dir);

    //�U������̈ʒu���v���C���[�̈ʒu����o��
    void AttackPosition(XMFLOAT3 _pos);

    //�U��
    void Attacking();
};