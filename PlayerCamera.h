#pragma once
#include "Engine/GameObject.h"
class PlayerCamera : public GameObject
{
    XMVECTOR moveVec_;

    Player* pPlayer_;

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

    //X����Y����]�s���Ԃ�
    XMMATRIX GetRotateX() { return XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)); }

    //�ʒu�iXMFLOAT3�j����J�����ʒu���o���܂��B
    void SetMoveVector(XMFLOAT3 pos){moveVec_ = XMLoadFloat3(&pos);}

    //�J�����̉�]�s���Ԃ��܂�
    XMFLOAT4X4 GetCameraRotateMatrix();
};