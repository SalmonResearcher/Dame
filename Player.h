#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "PlayerStateManager.h"

class Stage;

class Player :
    public GameObject
{
private:
    Transform tPlayer_; //�v���C���[�̃g�����X�t�H�[��
    Transform tCamera;  //�J�����̃g�����X�t�H�[��

    XMVECTOR vecPlayer_;    //�v���C���[�̐i��ł�������x�N�g��
    XMFLOAT3 movePlayer;

    XMFLOAT3 Camposition_;

    
    int hModel_;
    int hStage_;
    int hEnemy_;

    const float MAXSPEED = 0.15;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed_ = 0;
    short moveSpeed;
    short dash;
    float moveY = 0;
    bool isJumping = false;

protected:
    PlayerStateManager* pState_;

    Stage* pStage_;    //���f���ԍ����擾



public:
    //�v���C���[�̑傫���B
    // ��{�I�ɂ͒��������_�Ȃ̂�2�Ŋ���B
    const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

    Player(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void StageRay();
    void GetState() {};

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
        return 0;
    }


};

