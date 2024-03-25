#include "../../headers/geometry/Vector3D.hpp"

#include <cmath>
#include <iostream>
Vector3D::Vector3D() : x(0), y(0), z(0) {}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {
    fixVectorNearZero(*this);
}

void Vector3D::fixVectorNearZero(Vector3D &v)
{
    if (fabs(v.x) < epsilon)
        v.x = 0;
    if (fabs(v.y) < epsilon)
        v.y = 0;
    if (fabs(v.z) < epsilon)
        v.z = 0;
}

Vector3D Vector3D::operator+(Vector3D v)
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

// r = v * w
// r = vx * wx + vy * wy + vz * wz
float Vector3D::operator*(Vector3D v)
{
    return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator*(float scalar)
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

// Vectorial product
// vr = v1 × v2
// vr = (v1y * v2z - v1z * v2y, v1z * v2x - v1x * v2z, v1x * v2y - v1y * v2x)
Vector3D Vector3D::operator^(Vector3D v)
{
    float xResult = y * v.z - z * v.y;
    float yResult = z * v.x - x * v.z;
    float zResult = x * v.y - y * v.x;

    return Vector3D(xResult, yResult, zResult);
}

void Vector3D::normalize()
{
    float magnitude = sqrt(x * x + y * y + z * z);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}