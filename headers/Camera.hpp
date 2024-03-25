#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "./geometry.h"

class Camera
{
    public:
        Point3D position;
        Point3D target;
        Vector3D upVector;
        Vector3D direction;
        Vector3D sideVector;

        Camera();

        void setPosition(float x, float y, float z);

        void setUpVector(float x, float y, float z);

        void setTarget(float x, float y, float z);

        void verticalRotation(int angle);

        void horizontalRotation(int angle);

        void update();
};

#endif