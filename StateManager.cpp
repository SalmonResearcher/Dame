#include "StateManager.h"

//�R���X�g���N�^
StateManager::StateManager(GameObject* parent)
    :currentState_(nullptr),pParent_(parent)
{
}

//�f�X�g���N�^
StateManager::~StateManager()
{
    for (const auto& statePair : statesMap_)
    {
        statePair.second->ExitState();
        delete statePair.second;
    }
}

//��Ԃ̍X�V
void StateManager::Update()
{
    if (currentState_ != nullptr)
    {
        currentState_->UpdateState();
    }
}

//��Ԃ̕ύX
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

//��Ԃ�ǉ�
StateBase* StateManager::AddState(const std::string& stateName, StateBase* state)
{
    auto it = statesMap_.find(stateName);

    if (it != statesMap_.end())
    {
        // ���ɓ������O�̏�Ԃ����݂���ꍇ
        return it->second;
    }

    // ���݂��Ȃ��ꍇ�͏�Ԃ�o�^
    statesMap_[stateName] = state;
    return state;
}
