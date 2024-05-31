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

    int time_;
    bool isJumping_;


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

    void BulletDirection(XMVECTOR _dir) { playerForwardVec_ = _dir; };

    void BulletPosition(XMFLOAT3 _pos) {
        playerPos_ = _pos;
        // �e�ۂ̏����ʒu = �v���C���[�ʒu + (�O���x�N�g�� * �����I�t�Z�b�g)
        XMVECTOR bulletInitPos = XMLoadFloat3(&playerPos_) + (playerForwardVec_ * 0.5f);
        XMStoreFloat3(&initPos, bulletInitPos);
    };

    void BulletRotate(XMFLOAT3 _rote) { tJBullet_.rotate_.y = _rote.y + 180; };
};
