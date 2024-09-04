#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TutorialBoard : public GameObject
{
    //�`���[�g���A����\�������B1�`B7�܂�
    enum 
    {
        B_1,
        B_2,
        B_3,
        B_4,
        B_5,
        B_6,
        B_7,
        B_MAX
    };

    int hBoard_[B_MAX];
    Transform trBoard_[B_MAX];	//�X�e�[�W�v���r���[�̃g�����X�t�H�[��
    std::string name = "TutorialBoard";
    std::string number;
    std::string ext = ".fbx";

    Transform transSky_;


public:
    //�R���X�g���N�^
    TutorialBoard(GameObject* parent);

    //�f�X�g���N�^
    ~TutorialBoard();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};