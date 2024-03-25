#ifndef POINT3D_HPP
#define POINT3D_HPP

#include "Vector3D.hpp"

class Point3D
{
    public:
        float x, y, z;

        Point3D();

        Point3D(float x, float y, float z);

        Point3D operator+(Point3D p);

        Point3D operator+(Vector3D v);

        Point3D operator-(Point3D p);

        Point3D operator-(Vector3D v);

        float distance(Point3D p);
};

#endif