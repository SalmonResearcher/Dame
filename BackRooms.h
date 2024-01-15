#include "Engine/GameObject.h"

class BackRooms : public GameObject
{
    int hModel_;    //モデル番号
    Transform transBackRooms_;

public:
    //コンストラクタ
    BackRooms(GameObject* parent);

    //デストラクタ
    ~BackRooms();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデル番号を返す
    int GetModelHandle() { return hModel_; }
};