#pragma once
#include "Engine/GameObject.h"

class Enemy;

class JewelBullet :
    public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;

    XMFLOAT3 bulletPos_;

    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;

    int deleteTime_;
    int killCount_;
    int score_;

    /*�X�R�A���Z�̒萔����*/
    const int SCORE_BRACKETS[6] = { 25, 50, 75, 150, 300, 1500 };
    const int SCORE_BRACKET_THRESHOLD1 = 5;
    const int SCORE_BRACKET_THRESHOLD2 = 10;
    const int SCORE_BRACKET_COUNT = 6;
public:
    //�R���X�g���N�^
    JewelBullet(GameObject* parent);

    //�f�X�g���N�^
    ~JewelBullet();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    // �e�̕������v���C���[�̑O���x�N�g��������炤
    void BulletDirection(XMVECTOR _dir);

    // �e�̈ʒu���v���C���[�̈ʒu����Z�o����
    void BulletPosition(XMFLOAT3 _pos);
    void BulletPosition(float x, float y, float z);

    // �e�ۂ�Y����]�p�x�𓾂�
    void BulletRotate(XMFLOAT3 _rote) {transform_.rotate_.y = _rote.y + 180;};

    // �e��ł���
    void Shoot();

    // �����ɓ���������
    void OnCollision(GameObject* pTarget)override;

    // �G�̃L��������X�R�A���v�Z���܂�
    int CalculateScore(int killCount);

    void SetKillCount(int count);

    int SetStageHandle();
};
