#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "InputManager.h"


class PlayerCamera;
class StateManager;

class Player :public GameObject
{
private:
    int hModel_;    //���f���ԍ�
    int hSound_;    //�T�E���h�ԍ�
    int hGetSound_;

     int attackCountDown_;
    float jewelPitch_;   //���̍���
    float sordPitch_;

    int hStage_;    //�X�e�[�W���f���ԍ�
    int hEnemy_;    //�G�̃��f���ԍ�

    bool isJumping_; //�W�����v�����ǂ���

    float speed_ = 0.0f;
    float moveY_;   //Y���̉����x

    float jewelCount_;  //�����Ă����΂̐�
    float weight_;      //��΂̏d��
    int killCount_;     //�G��|������
    int jewelDeliver_;  //�^�񂾕�΂̐��d�͍ő��

    StateManager* pStateManager_;//��Ԃ�؂�ւ���
    PlayerCamera* pCamera_;

    bool attackEnd_;
    bool isHit_;

    RayCastData downRay;
    RayCastData play;

    // ���������_
    const XMFLOAT3 PLAYER_SIZE{ 1,1,1 };

    // �U�����̑҂����ԂƃJ�E���g�_�E��
    const int ATTACK_WAIT_TIME = 20;

    //���̃s�b�`
    const float MIN_SOUND_PITCH = 0.9f;
    const float MAX_SOUND_PITCH = 1.1f;

    //��΂̏d���i����O���[�o���Ō��߂�ꂽ�ق�������?�j
    const float JEWEL_WEIGHT = 0.01f;

    // �v���C���[�̉�����
    const float PLAYER_ACCELERATION = 0.006f;

    const float MAX_SPEED = 0.15f;

    const int WALKING_SPEED = 1;
    const int DASH_SPEED = 2;

    const float JUMP_VELOCITY = 0.4f;
    const float GRAVITY = 0.02f;
    const float MAX_GRAVITY = 0.5f; //�ő�d�ʉ�����

public:
    Player(GameObject* parent);     //�R���X�g���N�^
    ~Player();                      //�f�X�g���N�^

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //����

    void Walk();        //����
    void Jump();        //�W�����v
    void Run();         //����
    void Attacking();   //�U��
    void Knockback();   //�͂�����

    bool IsJumping();   //�ڒn���Ă��邩

    void AddGravity();  //�d�͂��v���C���[�ɉ��Z

    void AddMovement(XMVECTOR moveVector, float run);   //�v���C���[�̈ړ��x�N�g�����v�Z

    XMVECTOR CalcMovementInput();

    XMFLOAT3 GetPlayerPosition() { return transform_.position_; };

    void OnCollision(GameObject* pTarget)override;  //�����ƂԂ�������

    // �Q�b�^�[�ƃZ�b�^�[
    int GetModelHandle() { return hModel_; }

    int SendJewel() { return jewelDeliver_; };        //��Δ��ɔ[�i������΂̐��𑗂�܂�
    int GetJewelCount();    //����Ɏ����Ă����΂̐���Ԃ��܂�

    void KillCountUp();     //�v���C���[�����ړG��|��������1���₵�܂�
    int GetKillCount();     //�v���C���[�����ړ|�����G�̐���Ԃ��܂��B

    void SetVelocityY(float vY) { moveY_ = vY; };
    float GetVelocityY() { return moveY_; };

    void SetJumping(bool flag) { isJumping_ = flag; }

    void SetMoveY(float moveY) { transform_.position_.y += moveY; }

    XMVECTOR GetKnockbackDirection();

    int SetStageHandle();

    void RotatePlayer(XMVECTOR moveVector);
    void RotatePlayer();

    //�v���C���[�̏d�ʂ�Ԃ��܂�
    float GetWeight();

    //�v���C���[�̑��x��Ԃ��܂��B
    float GetSpeed();

    //�v���C���[�̍U�����I�������true
    bool IsAttackEnd();

    //Float�̃����_���Ȓl�𐶐����܂�
    float GenerateRandomFloat(float min, float max);
};