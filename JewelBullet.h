#pragma once
#include "Engine/GameObject.h"
class JewelBullet :
    public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;

    Transform tJBullet_;
    XMVECTOR playerForwardVec_;
    XMFLOAT3 playerPos_;

    XMVECTOR bulletInitPos;
    XMFLOAT3 initPos;

    int deleteTime_;


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
    void BulletDirection(XMVECTOR _dir) { playerForwardVec_ = _dir; };

    /// <summary>
    /// �e�̈ʒu���v���C���[�̈ʒu����Z�o����
    /// </summary>
    void BulletPosition(XMFLOAT3 _pos) {
        playerPos_ = _pos;
        // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
        XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
        XMStoreFloat3(&initPos, bulletInitPos);
    };

    /// <summary>
    /// �e�̉�]���󂯎��
    /// </summary>
    void BulletRotate(XMFLOAT3 _rote) { tJBullet_.rotate_.y = _rote.y + 180; };

    /// <summary>
    /// �e��ł���
    /// </summary>
    void Shoot();

    /// <summary>
    /// �����ɓ���������
    /// </summary>
    void OnCollision(GameObject* pTarget)override;

};
