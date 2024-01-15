#include "Engine/GameObject.h"

class BackRooms : public GameObject
{
    int hModel_;    //���f���ԍ�
    Transform transBackRooms_;

public:
    //�R���X�g���N�^
    BackRooms(GameObject* parent);

    //�f�X�g���N�^
    ~BackRooms();

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