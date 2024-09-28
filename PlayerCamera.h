#pragma once
#include "Engine/GameObject.h"

class Player;

class PlayerCamera : public GameObject
{
    XMVECTOR moveVec_;

    Player* pPlayer_;

    // 定数の定義
    const float MOUSE_SENSITIVITY_INCREMENT_NORMAL = 0.1f;
    const float MOUSE_SENSITIVITY_INCREMENT_FAST = 0.5f;
    const float MOUSE_SENSITIVITY_MIN = 0.01f; // 最小感度
    const float MOUSE_SENSITIVITY_MAX = 5.0f;  // 最大感度
    const float CAM_MOVE_SCALE = 0.1f;
    const float MAX_LOOK_UP = 75.0f;
    const float MIN_LOOK_DOWN = -85.0f;
public:
    //コンストラクタ

    PlayerCamera(GameObject* parent);

    //デストラクタ
    ~PlayerCamera();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    //Y軸の回転行列を返す
    XMMATRIX GetRotateY(){ return XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); }

    //X軸の回転行列を返す
    XMMATRIX GetRotateX() { return XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)); }

    //位置（XMFLOAT3）からカメラ位置を出します。
    void SetMoveVector(XMFLOAT3 pos){moveVec_ = XMLoadFloat3(&pos);}

    //カメラの回転行列を返します
    XMFLOAT4X4 GetCameraRotateMatrix();

    XMFLOAT3 GetCameraPosition() { return transform_.position_; };

    float Clamp(float value, float min, float max);
};