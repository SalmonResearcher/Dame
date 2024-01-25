#pragma once
#include "Engine/GameObject.h"

class Sprite;

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_;    //モデル番号
    int hModel_2;
    Transform transStage_;
    Transform transSky_;

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

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