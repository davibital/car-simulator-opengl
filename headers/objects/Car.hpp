#ifndef CAR_HPP
#define CAR_HPP

#include <stdio.h>
#include "../geometry.h"
#include <vector>
#include <string>

using namespace std;

bool is_number(const std::string& s);

class Car{
public:
    Point3D position; 
    vector<Point3D> vertices;
    vector<Point3D> vetor_textura;
    vector<Vector3D> normals;
    vector<vector<vector<int> > > faces;
    Vector3D direction;
    Vector3D upVector;
    Vector3D sideVector;

    Car();

    void setPosition(float x, float y, float z);

    void setUpVector(float x, float y, float z);

    void setDirection(float x, float y, float z);

    void moveFoward();

    void moveBackward();

    void moveRight();

    void moveLeft();

    void horizontalRotation(int angle);

    void verticalRotation(int angle);

    void drawCar();

    bool loadObjCar(const char* filename);
};

#endif