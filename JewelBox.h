#pragma once
#include "Engine/GameObject.h"

class Player;

//�[�i�����Ǘ�����N���X
class JewelBox : public GameObject
{
    int hModel_;    //���f���ԍ�

    int jewel_;
    int score_;

    const XMFLOAT3 COLLIDER_POSITION = { 0,1,0 };
    const float COLLIDER_RADIUS = 1.5f;

public:
    //�R���X�g���N�^
    JewelBox(GameObject* parent);

    //�f�X�g���N�^
    ~JewelBox();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���ԍ���Ԃ�
    int GetModelHandle() { return hModel_; };

    void OnCollision(GameObject* pTarget);

    void AddScore(int _score) { score_ += _score; };

    int ReturnJewel() { return jewel_; };
    int GetKillScore() { return score_; };
    int SetStageHandle();
};