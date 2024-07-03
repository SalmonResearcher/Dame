#include "StateManager.h"

//コンストラクタ
StateManager::StateManager(GameObject* parent)
    :currentState_(nullptr),pParent_(parent)
{
}

//デストラクタ
StateManager::~StateManager()
{
    for (const auto& statePair : statesMap_)
    {
        statePair.second->ExitState();
        delete statePair.second;
    }
}

//状態の更新
void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

//状態の変更
void StateManager::ChangeState(const std::string& stateName)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        if (currentState_ != nullptr)
        {
            currentState_->ExitState();
        }

        currentState_ = it->second;
        currentState_->EnterState();
    }
}

//状態を追加
StateBase* StateManager::AddState(const std::string& stateName, StateBase* state)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        // 既に同じ名前の状態が存在する場合
        return it->second;
    }

    // 存在しない場合は状態を登録
    statesMap_[stateName] = state;
    return state;
}
