#pragma once
#include "Engine/GameObject.h"

//納品箱を管理するクラス
class JewelBox : public GameObject
{
    int hModel_;    //モデル番号
    Transform trBox_;

    int anim_Start;
    int anim_End;


public:
    //コンストラクタ
    JewelBox(GameObject* parent);

    //デストラクタ
    ~JewelBox();

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

    void OnCollision(GameObject* pTarget);

};