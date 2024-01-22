#pragma once
#include "Engine/GameObject.h"


class Player :
    public GameObject
{
private:
    Transform tPlayer_; //�v���C���[�̃g�����X�t�H�[��
    Transform tCamera;  //�J�����̃g�����X�t�H�[��

    XMVECTOR vecPlayer_;    //�v���C���[�̌����Ă�������x�N�g��
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;


    int hModel_;
    const float SPEED = 0.15;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;



    XMFLOAT3 GetPlayerPos()
    {
        return tPlayer_.position_;
    }
};

