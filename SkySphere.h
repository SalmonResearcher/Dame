#pragma once
#include "Engine/GameObject.h"

class Player;

//�󋅂��Ǘ�����N���X
class SkySphere : public GameObject
{
    Player* pPlayer_;

    int hModel_;    //���f���ԍ�

    const float ROTATE_SPEED = 0.01f;
    const XMFLOAT3 SCALE = { 0.75f,0.75f,0.75f };
public:
    //�R���X�g���N�^
    SkySphere(GameObject* parent);

    //�f�X�g���N�^
    ~SkySphere();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���ԍ���Ԃ�
    int GetModelHandle() { return hModel_; }
};