#include <cmath>
#include <iostream>
#include "../../headers/geometry/Quaternion.hpp"
#include "../../headers/geometry/Vector3D.hpp"

Quaternion::Quaternion() : w(0), x(0), y(0), z(0) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(int angle, Vector3D v)
{
    float radians = angle * M_PI / 180.0;

    w = cos(radians / 2);
    x = v.x * sin(radians / 2);
    y = v.y * sin(radians / 2);
    z = v.z * sin(radians / 2);
}

// p = (s1, v1)
// q = (s2, v2)
// p * q = (s1, v1)(s2, v2) = (s1 * s2 - v1 * v2, s1 * v2 + s2 * v1 + v1 x v2)
Quaternion Quaternion::operator*(Quaternion q)
{
    Vector3D pVector = Vector3D(x, y, z);
    Vector3D qVector = Vector3D(q.x, q.y, q.z);

    float wResult = (w * q.w) - (pVector * qVector);

    Vector3D s1v2 = pVector * q.w;
    Vector3D s2v1 = qVector * w;

    Vector3D v = (s1v2 + s2v1) + (pVector ^ qVector);

    return Quaternion(wResult, v.x, v.y, v.z);
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(w, -x, -y, -z);
}

void Quaternion::normalize()
{
    float magnitude = sqrt(w * w + x * x + y * y + z * z);
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

// r = q * p * q'
// p = (0, v)
// q' = q.conjugate()
Vector3D Quaternion::rotate(Vector3D v)
{
    Quaternion vQuaternion = Quaternion(0, v.x, v.y, v.z);

    Quaternion finalRotation = *this * vQuaternion * conjugate();

    return Vector3D(finalRotation.x, finalRotation.y, finalRotation.z);
}