#pragma once
#include "Engine/GameObject.h"

class Player;

class PlayerCamera : public GameObject
{
    XMVECTOR moveVec_;

    Player* pPlayer_;

    // �萔�̒�`
    const float MOUSE_SENSITIVITY_INCREMENT_NORMAL = 0.1f;
    const float MOUSE_SENSITIVITY_INCREMENT_FAST = 0.5f;
    const float MOUSE_SENSITIVITY_MIN = 0.01f; // �ŏ����x
    const float MOUSE_SENSITIVITY_MAX = 5.0f;  // �ő労�x
    const float CAM_MOVE_SCALE = 0.1f;
    const float MAX_LOOK_UP = 75.0f;
    const float MIN_LOOK_DOWN = -85.0f;
public:
    //�R���X�g���N�^

    PlayerCamera(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerCamera();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    //Y���̉�]�s���Ԃ�
    XMMATRIX GetRotateY(){ return XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); }

    //X���̉�]�s���Ԃ�
    XMMATRIX GetRotateX() { return XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)); }

    //�ʒu�iXMFLOAT3�j����J�����ʒu���o���܂��B
    void SetMoveVector(XMFLOAT3 pos){moveVec_ = XMLoadFloat3(&pos);}

    //�J�����̉�]�s���Ԃ��܂�
    XMFLOAT4X4 GetCameraRotateMatrix();

    XMFLOAT3 GetCameraPosition() { return transform_.position_; };

    float Clamp(float value, float min, float max);
};