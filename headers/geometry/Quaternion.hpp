#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector3D.hpp"

class Quaternion
{
    public:
        float w, x, y, z;

        Quaternion();

        Quaternion(float w, float x, float y, float z);

        Quaternion(int angle, Vector3D v);

        Quaternion operator*(Quaternion q);

        Quaternion conjugate();

        void normalize();

        Vector3D rotate(Vector3D v);
};

#endif