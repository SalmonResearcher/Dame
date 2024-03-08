#pragma once
#include "Engine/GameObject.h"
class Cammera : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMFLOAT3 move_ = { 0,0,0 };
    int time;

public:
    //�R���X�g���N�^
    Cammera(GameObject* parent);

    //�f�X�g���N�^
    ~Cammera();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetPlayerVector(XMVECTOR _vecPlayer);
    void GetPlayerPosition(XMFLOAT3 _playerPos);
};