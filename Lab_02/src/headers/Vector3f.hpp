#pragma once

class Vector3f {

    private:
    float x, y, z;

    public:
    Vector3f();
    Vector3f(float x, float y, float z);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    Vector3f operator+(const Vector3f& vec);
    Vector3f operator/(float val);

    ~Vector3f() = default;

};