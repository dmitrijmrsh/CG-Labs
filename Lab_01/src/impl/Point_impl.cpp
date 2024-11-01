#include "/home/dmitriimrsh/Projects/Labs/CG-Labs/Lab_01/src/headers/Point.hpp"

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

Point Point::rotatePoint(const Point& p, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    
    return {p.x * cosA - p.y * sinA, p.x * sinA + p.y * cosA};
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}