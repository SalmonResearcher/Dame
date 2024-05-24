#include "Rectangle.h"
#include <iostream>

int main() {
    // 与えられた2つの点で四角形を作成
    Rectangle rectangle(5, 7, 15, 0);

    // 面積を計算して出力
    float area = rectangle.CalculateArea();
    std::cout << "Rectangle area: " << area << std::endl;

    return 0;
}
