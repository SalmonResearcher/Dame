#include "MovingState.h"


// MovingState.cpp

float MovingState::GetGroundHeight(const XMFLOAT3& position, Player* _player)
{
    RayCastData down;
    down.start = { position.x, position.y + 1.0f, position.z };  // プレイヤーの少し上から発射
    down.dir = XMFLOAT3(0, -1, 0);  // 下向きに発射

    // レイキャストを実行
    Model::RayCast(_player->GetStageHandle(), &down);

    if (down.hit)
    {
        // レイが地面に当たった場合、その高さを返す
        return down.start.y - down.dist;
    }
    else
    {
        // レイが当たらなかった場合のデフォルト値（例：非常に低い値）
        return -1000.0f;
    }
}

void MovingState::Update(Player* _player)
{
    // 移動処理
    XMVECTOR moveVector = CalculateMoveVector(_player);

    // 速度の更新
    UpdateSpeed();

    // プレイヤーの位置を更新
    XMFLOAT3 currentPos = _player->GetPosition();
    XMVECTOR playerPos = XMLoadFloat3(&currentPos);
    playerPos += moveVector * speed_;

    XMFLOAT3 newPos;
    XMStoreFloat3(&newPos, playerPos);

    // 地面との接地処理
    float groundHeight = GetGroundHeight(newPos, _player);
    newPos.y = groundHeight + _player->GetHeight() / 2;  // プレイヤーの中心が地面上になるように調整

    _player->SetPosition(newPos);

    // 状態遷移のチェック
    CheckStateTransition(_player);
}