#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_02/src/headers/Vector3f.hpp"

Vector3f::Vector3f() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3f::Vector3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3f::getX() const {
    return x;
}

float Vector3f::getY() const {
    return y;
}

float Vector3f::getZ() const {
    return z;
}

void Vector3f::setX(float x) {
    this->x = x;
}

void Vector3f::setY(float y) {
    this->y = y;
}

void Vector3f::setZ(float z) {
    this->z = z;
}

Vector3f Vector3f::operator+(const Vector3f& vec) {
    return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}

Vector3f Vector3f::operator/(float val) {
    return Vector3f(x / val, y / val, z / val);
}