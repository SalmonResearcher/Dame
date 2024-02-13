#pragma once
#include "Engine/GameObject.h"
class Jewel :
    public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;

    Transform trJewel_;

    float rotY = 0.0f;
    float grabity_ = 0.0f;
    int time;
    bool jewelRotate_;

public:
    //�R���X�g���N�^
    Jewel(GameObject* parent);

    //�f�X�g���N�^
    ~Jewel();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};
