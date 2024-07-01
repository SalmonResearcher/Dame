#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "InputManager.h"


class Stage;
class StateManager;

class Player :public GameObject
{
private:

    int hModel_;    //���f���ԍ�

    int hStage_;    //�X�e�[�W���f���ԍ�

    int hEnemy_;    //�G�̃��f���ԍ�

    bool isJumping_; //�W�����v�����ǂ���

    float moveY_;   //Y���̉����x

    float jewelCount_;  //�����Ă����΂̐�
    float weight_;      //��΂̏d��
    int killCount_;     //�G��|������
    int jewelDeliver_;  //�^�񂾕�΂̐�

    StateManager* pStateManager_;//��Ԃ�؂�ւ���

public:
    Player(GameObject* parent);     //�R���X�g���N�^
    ~Player();                      //�f�X�g���N�^

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //����

    void Walk();    //����
    void Jump();    //�W�����v
    void Run();     //����
    void Attack();
    void Knockback();//�͂�����

    bool IsJumping();//�ڒn���Ă��邩











    //void ChangeState(PlayerState* newState);

    void OnCollision(GameObject* pTarget)override;


    XMFLOAT3 GetPlayerPos() { return transform_.position_; };

    XMVECTOR GetPlayerVec();

    // �Q�b�^�[�ƃZ�b�^�[
   // PlayerCamera& GetCamera() { return camera_; }
    int GetModelHandle() const { return hModel_; }

    int SendJewel() { return jewelDeliver_; };        //��Δ��ɔ[�i������΂̐��𑗂�܂�
    int GetJewelCount();    //����Ɏ����Ă����΂̐���Ԃ��܂�

    void KillCountUp();     //�v���C���[�����ړG��|��������1���₵�܂�
    int GetKillCount();     //�v���C���[�����ړ|�����G�̐���Ԃ��܂��B

    void SetVelocityY(float vY) { moveY_ = vY; };
    float GetVelocityY() { return moveY_; };

    void SetJumping(bool flag) { isJumping = flag; }

    void SetMoveY(float moveY) { transform_.position_.y += moveY; }

    XMVECTOR GetKnockbackDirection();

    int GetStageHandle() { return hStage_; }
};