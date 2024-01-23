#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"

class Stage;

class Player :
    public GameObject
{
private:
    Transform tPlayer_; //�v���C���[�̃g�����X�t�H�[��
    Transform tCamera;  //�J�����̃g�����X�t�H�[��

    XMVECTOR vecPlayer_;    //�v���C���[�̌����Ă�������x�N�g��
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;

    const XMFLOAT3 PLAYERSIZE{ 1,1,1 };
    int hModel_;
    const float MAXSPEED = 0.15;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed_ = 0;
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

    Stage* pStage;    //���f���ԍ����擾
    int hStage_;//�X�e�[�W���f���̔ԍ�

public:
    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void StageRay();


    XMFLOAT3 GetPlayerPos()
    {
        return tPlayer_.position_;
    }

    XMVECTOR GetPlayerVec()
    {
        return vecPlayer_;
    }

    //�v���C���[�����肷��X�e�[�W
    int GetPlayerStage()
    {
        return 
    }
};

