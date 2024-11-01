#pragma once

#include <cmath>
#include <vector>

class Point {

    private:
    float x, y;

    public:
    Point() = default;
    Point(float x, float y);

    static Point rotatePoint(const Point& p, float angle);

    float getX();
    float getY();

    void setX(float x);
    void setY(float y);

    ~Point() = default;

};