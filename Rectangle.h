#pragma once

// �l�p�`��\���N���X
class Rectangle {
private:
    float x1, z1; // ����̍��W
    float x2, z2; // �E���̍��W

public:
    // �R���X�g���N�^
    Rectangle(float _x1, float _z1, float _x2, float _z2) : x1(_x1), z1(_z1), x2(_x2), z2(_z2) {}

    // �ʐς��v�Z���郁�\�b�h
    float CalculateArea() const {
        float width = x2 - x1;
        float height = z1 - z2;
        return width * height;
    }
};
