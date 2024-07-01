#pragma once
#include "Engine/GameObject.h"

class Sprite;
class Player;
class Stage;
class Jewel;

//���������Ǘ�����N���X
class Stage : public GameObject
{
    Player* pPlayer_;
    Stage* pStage_;
    Jewel* pJewel_;


    int hModel_;    //���f���ԍ�
    int hModel2_;
    Transform transStage_;
    Transform transSky_;

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���ԍ���Ԃ�
    int GetModelHandle() { return hModel_; }
};