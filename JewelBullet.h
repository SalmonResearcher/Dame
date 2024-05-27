#pragma once
#include "Engine/GameObject.h"
class JewelBullet :
    public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;

    Transform trJBullet_;
    XMVECTOR jewelDir_;
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

    void Shoot();

    //Jewel Shoot Direction / XMVECTOR Start, XMVECTOR End
    void SetDirection(XMVECTOR _dirStart) { jewelDir_ = _dirStart; };
};
