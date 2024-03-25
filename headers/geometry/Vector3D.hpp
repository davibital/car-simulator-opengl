#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

class Vector3D
{
    private:
        float epsilon = 1e-6;

        void fixVectorNearZero(Vector3D &v);

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