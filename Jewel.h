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
    int time_;
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

    //�C�[�W���O�֐�
    float easeInOutCubic(float x) {
        return x < 0.5 ? 4 * pow(x, 3) : 1 - pow(-2 * x + 2, 3) / 2;
    }

    void Shoot();

};
