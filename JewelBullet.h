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

    /// <summary>
    /// �e�̕������v���C���[�̑O���x�N�g��������炤
    /// </summary>
    /// <param name="_dir">XMVECTOR�F�����x�N�g��</param>
    void BulletDirection(XMVECTOR _dir);

    /// <summary>
    /// �e�̈ʒu���v���C���[�̈ʒu����Z�o����
    /// </summary>
    void BulletPosition(XMFLOAT3 _pos);

    /// <summary>
    /// �e�ۂ�Y����]�p�x�𓾂�
    /// </summary>
    /// <param name="_rote"></param>
    void BulletRotate(XMFLOAT3 _rote) {transform_.rotate_.y = _rote.y + 180;};
    /// <summary>
    /// �e��ł���
    /// </summary>
    void Shoot();

    /// <summary>
    /// �����ɓ���������
    /// </summary>
    void OnCollision(GameObject* pTarget)override;

    /// <summary>
    /// �G�̃L��������X�R�A���v�Z���܂�
    /// </summary>
    int CalculateScore(int killCount);


    void SetKillCount(int count);
};
