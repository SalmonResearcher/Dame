#pragma once
#include "Engine/GameObject.h"

//�[�i�����Ǘ�����N���X
class JewelBox : public GameObject
{
    int hModel_;    //���f���ԍ�
    Transform trBox_;

    int anim_Start;
    int anim_End;


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
    int GetModelHandle() { return hModel_; }

    void OnCollision(GameObject* pTarget);

};