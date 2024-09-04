#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class TutorialBoard : public GameObject
{
    //チュートリアルを表示する板B1～B7まで
    enum 
    {
        B_1,
        B_2,
        B_3,
        B_4,
        B_5,
        B_6,
        B_7,
        B_MAX
    };

    int hBoard_[B_MAX];
    Transform trBoard_[B_MAX];	//ステージプレビューのトランスフォーム
    std::string name = "TutorialBoard";
    std::string number;
    std::string ext = ".fbx";

    Transform transSky_;


public:
    //コンストラクタ
    TutorialBoard(GameObject* parent);

    //デストラクタ
    ~TutorialBoard();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};