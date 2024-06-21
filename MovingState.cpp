#include "MovingState.h"
#include "Player.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "Engine/Input.h"


using namespace DirectX;

void MovingState::Enter(Player* player)
{
    speed_ = 0.0f;
}

void MovingState::Update(Player* _player)
{
    // 移動処理
    XMVECTOR moveVector = CalculateMoveVector(_player);

    // 速度の更新
    UpdateSpeed();

    // プレイヤーの位置を更新
    XMVECTOR playerPos = XMLoadFloat3(&_player->GetPlayerPos());
    playerPos += moveVector * speed_;
    XMFLOAT3 newPos;
    XMStoreFloat3(&newPos, playerPos);
    _player->SetPosition(newPos);

    // 状態遷移のチェック
    CheckStateTransition(_player);
}

void MovingState::Exit(Player* player)
{
    // 必要に応じて終了処理を記述
}

XMVECTOR MovingState::CalculateMoveVector(Player* player)
{
    XMVECTOR moveVector = XMVectorZero();
    if (Input::IsKey(DIK_W)) moveVector += player->GetForwardVector();
    if (Input::IsKey(DIK_S)) moveVector -= player->GetForwardVector();
    if (Input::IsKey(DIK_A)) moveVector -= player->GetRightVector();
    if (Input::IsKey(DIK_D)) moveVector += player->GetRightVector();

    return XMVector3Normalize(moveVector);
}

void MovingState::UpdateSpeed()
{
    if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
    {
        speed_ += ACCELERATION;
        if (speed_ > MAX_SPEED) speed_ = MAX_SPEED;
    }
    else
    {
        speed_ -= DECELERATION;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }
}

void MovingState::CheckStateTransition(Player* player)
{
    if (speed_ == 0.0f)
    {
        player->ChangeState(new IdleState());
    }
    else if (Input::IsKeyDown(DIK_SPACE))
    {
        player->ChangeState(new JumpingState());
    }
    // 他の状態遷移条件をここに追加
}

float MovingState::GetGroundHeight(const XMFLOAT3& position, Player* _player)
{
    // 地面の高さを取得するロジックをここに追加
    return 0.0f; // 仮の実装
}


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