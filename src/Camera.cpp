#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "../headers/Camera.hpp"

Camera::Camera()
{
    position = Point3D(0, 0, 0);
    target = Point3D(0, 0, 0);
    upVector = Vector3D(0, 0, 0);
    direction = Vector3D(0, 0, 0);
    sideVector = direction ^ upVector;
    isThirdCarView = false;
}

void Camera::enableThirdCarView()
{
    isThirdCarView = true;
}

void Camera::disableThirdCarView()
{
    isThirdCarView = false;
}

void Camera::setPosition(float x, float y, float z)
{
    position = Point3D(x, y, z);
}

void Camera::setUpVector(float x, float y, float z)
{
    upVector = Vector3D(x, y, z);
    upVector.normalize();
}

void Camera::setTarget(float x, float y, float z)
{
    target = Point3D(x, y, z);

    direction = Vector3D(target.x - position.x, target.y - position.y, target.z - position.z);
    direction.normalize();

    sideVector = direction ^ upVector;
    sideVector.normalize();

    upVector = sideVector ^ direction;
    upVector.normalize();
}

void Camera::verticalRotation(int angle)
{
    Quaternion rotationQ = Quaternion(angle, sideVector);
    rotationQ.normalize();

    direction = rotationQ.rotate(direction);
    direction.normalize();

    upVector = rotationQ.rotate(upVector);
    upVector.normalize();
}

void Camera::horizontalRotation(int angle)
{
    Quaternion rotationQ = Quaternion(angle, upVector);
    rotationQ.normalize();

    direction = rotationQ.rotate(direction);
    direction.normalize();

    sideVector = rotationQ.rotate(sideVector);
    sideVector.normalize();
}

void Camera::moveUp()
{
    position = position + upVector;
}

void Camera::moveDown()
{
    position = position - upVector;
}

void Camera::moveForward()
{
    position = position + direction;
}

void Camera::moveRight()
{
    position = position + sideVector;
}

void Camera::moveLeft()
{
    position = position - sideVector;
}

void Camera::moveBackward()
{
    position = position - direction;
}

void Camera::thirdCarView(Car car)
{
    if (!isThirdCarView)
        return;
        
    Quaternion rotationQ = Quaternion(45, car.sideVector);
    rotationQ.normalize();

    Vector3D viewVector = rotationQ.rotate(car.upVector);

    position = car.position + (viewVector * 4);
    target = car.position + (car.direction * 2);

    direction = Vector3D(target.x - position.x, target.y - position.y, target.z - position.z);
    direction.normalize();

    upVector = car.sideVector ^ direction;
    upVector.normalize();

    sideVector = direction ^ upVector;
    sideVector.normalize();
}

void Camera::update()
{
    target = position + direction;

    gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z, upVector.x, upVector.y, upVector.z);
}