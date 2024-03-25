#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
    public:
        float x, y, z;

        Vector3D();

        Vector3D(float x, float y, float z);

        Vector3D operator+(Vector3D v);

        float operator*(Vector3D v);

        Vector3D operator*(float scalar);

        Vector3D operator^(Vector3D v);

        void normalize();
};

#endif