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
    XMFLOAT3 smoothCam;
    
    int hModel_;
    int hStage_;
    int hEnemy_;

    float mouseSens = 1;

    float attackStart;
    float attackEnd;
    const float JEWEL_WEIGHT = 0.05f;

    const float MAXSPEED = 0.15f;  //�J�����̉�]���x,�v���C���[�̈ړ����x
    float speed_ = 0;
    float jewelCount_;
    float weight_;
    short moveSpeed;
    short dash_;
    float moveY = 0;
    bool isJumping = false;
    bool isHit;

    int onCollisionTime = 0;


    int killCount_;
    int jewelDeliver_;

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

    void OnCollision(GameObject* pTarget)override;

    int SendJewel(){ return jewelDeliver_; }
    int GetJewelCount() { return jewelCount_; }

    void KillCountUp() { killCount_++; }
    int GetKillCount() { return killCount_; }
};

