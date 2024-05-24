#pragma once

// 四角形を表すクラス
class Rectangle {
private:
    float x1, z1; // 左上の座標
    float x2, z2; // 右下の座標

public:
    // コンストラクタ
    Rectangle(float _x1, float _z1, float _x2, float _z2) : x1(_x1), z1(_z1), x2(_x2), z2(_z2) {}

    // 面積を計算するメソッド
    float CalculateArea() const {
        float width = x2 - x1;
        float height = z1 - z2;
        return width * height;
    }
};
