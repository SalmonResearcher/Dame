#pragma once
#include "Engine/GameObject.h"
class PlayerCamera : public GameObject
{
    XMVECTOR moveVec_;

    Player* pPlayer_;

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

    //X軸のY軸回転行列を返す
    XMMATRIX GetRotateX() { return XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)); }

    //位置（XMFLOAT3）からカメラ位置を出します。
    void SetMoveVector(XMFLOAT3 pos){moveVec_ = XMLoadFloat3(&pos);}

    //カメラの回転行列を返します
    XMFLOAT4X4 GetCameraRotateMatrix();
};