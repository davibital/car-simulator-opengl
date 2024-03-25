#include <cmath>
#include "../../headers/geometry/Point3D.hpp"

Point3D::Point3D() : x(0), y(0), z(0) {}

Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

Point3D Point3D::operator+(Point3D p)
{
    return Point3D(x + p.x, y + p.y, z + p.z);
}

Point3D Point3D::operator+(Vector3D v)
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

float Point3D::distance(Point3D p)
{
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2));
}