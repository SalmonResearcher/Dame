#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

class Fafro : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hStage_;
    Transform transFafro_;
    XMFLOAT3 target_;
    float moveY = 0.0f;

    bool isJumping;
    int startFrame;
    int endFrame;
    float animeSpeed;


public:
    //�R���X�g���N�^
    Fafro(GameObject* parent);

    //�f�X�g���N�^
    ~Fafro();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetTargetPosition(XMFLOAT3 _target) { target_ = _target; };

    int GetModelHandle() { return hModel_; }

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;


};