#pragma once
#include "Engine/GameObject.h"
class EnemySpawn : public GameObject
{
    int interval_;  //�ZF�o�߂�����X�|�[��
    int time_;      //1F���ƂɃJ�E���g
    bool canSpawn;
    int limit;
public:
    //�R���X�g���N�^
    EnemySpawn(GameObject* parent);

    //�f�X�g���N�^
    ~EnemySpawn();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�X�|�[���|�C���g��ݒ�
    void SetSpawnPoint(XMFLOAT3 point) { transform_.position_ = point; }
    XMFLOAT3 GetSpawnPoint() { return transform_.position_; };

    //�X�|�[������X�|�[���܂ł̍��Ԏ��ԁi1F�P�ʁj
    void SetInterval(int _interval) { interval_ = _interval; };

    void StartSpawn() { canSpawn = true; };
    void StopSpawn() { canSpawn = false; };

    float getRandomFloat(float min, float max);
};