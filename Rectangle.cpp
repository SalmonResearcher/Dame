#include "Rectangle.h"
#include <iostream>

int main() {
    // �^����ꂽ2�̓_�Ŏl�p�`���쐬
    Rectangle rectangle(5, 7, 15, 0);

    // �ʐς��v�Z���ďo��
    float area = rectangle.CalculateArea();
    std::cout << "Rectangle area: " << area << std::endl;

    return 0;
}
