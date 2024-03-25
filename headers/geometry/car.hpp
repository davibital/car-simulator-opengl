#include <stdio.h>
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <vector>
#include <string>

using namespace std;

class Car{
public:
    Car(Point3D pos, Vector3D dir);
    Point3D position; 
    vector<Point3D> vertices;
    vector<Point3D> vetor_textura;
    vector<Vector3D> normals;
    vector<vector<vector<int> > > faces;
    Vector3D direction;

    void drawCar();

    bool loadObjCar(const char* filename);

    bool is_number(const std::string& s);
};