#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "terrain/terrainData.cpp"
#include "../headers/Camera.hpp"
#include "../headers/objects/Car.hpp"

using namespace std;

vector<vector<int>> terrainMatrix;
int terrainWidth, terrainLength;
int maxTerrainHeight;

Camera camera;
Car car;

void init();
void display();
void reshape(int w, int h);

void initTerrain();

void drawTerrainMesh();
void rotateCamera(int key, int x, int y);
void carMovement(unsigned char key, int x, int y);

int main(int argc, char **argv)
{
    readPPMFile(argv[1]);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Terrain");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(rotateCamera);
    glutKeyboardFunc(carMovement);

    glutMainLoop();

    return 0;
}

void init()
{
    initTerrain();

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.5, 100.0);

    camera.setPosition(terrainWidth, terrainLength, maxTerrainHeight * 1.2);
    camera.setUpVector(0.0, 0.0, 0.1);
    camera.setTarget(0, 0, 0);

    car.loadObjCar("../obj/car.obj");
    car.setPosition(1, 1, matrix[1][1] + 0.3);
    car.setUpVector(0, 0, 1);
    car.setDirection(0.707, 0.707, 0);

    camera.enableThirdCarView();
    camera.thirdCarView(car);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.update();

    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1000.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1000.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1000.0);
    glEnd();

    drawTerrainMesh();

    car.drawCar();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void initTerrain()
{
    terrainWidth = getTerrainWidth();
    terrainLength = getTerrainLength();
    terrainMatrix = getTerrainMatrix();

    maxTerrainHeight = getMaxHeight();
}

void drawTerrainMesh()
{
    float r = 0.5, g = 0.2, b = 0.7;
    for (int i = 0; i < terrainLength; i++)
    {
        for (int j = 0; j < terrainWidth; j++)
        {
            if (r > 1)
                r = r - 1;
            if (g > 1)
                g = g - 1;
            if (b > 1)
                b = b - 1;

            if (i + 1 < terrainLength && j + 1 < terrainWidth)
            {
                glColor3f(r, g, b);
                glBegin(GL_TRIANGLES);
                    glVertex3f(j, i, terrainMatrix[i][j]);
                    glVertex3f(j, i + 1, terrainMatrix[i + 1][j]);
                    glVertex3f(j + 1, i, terrainMatrix[i][j + 1]);
                glEnd();
            }

            r += 0.1;
            g += 0.2;
            b += 0.3;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                glColor3f(r, g, b);
                glBegin(GL_TRIANGLES);
                    glVertex3f(j, i, terrainMatrix[i][j]);
                    glVertex3f(j, i - 1, terrainMatrix[i - 1][j]);
                    glVertex3f(j - 1, i, terrainMatrix[i][j - 1]);
                glEnd();
            }

            r += 0.1;
            g += 0.2;
            b += 0.3;
        }
    }
}

void rotateCamera(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        camera.verticalRotation(3);
        break;
    case GLUT_KEY_DOWN:
        camera.verticalRotation(-3);
        break;
    case GLUT_KEY_LEFT:
        camera.horizontalRotation(3);
        break;
    case GLUT_KEY_RIGHT:
        camera.horizontalRotation(-3);
        break;
    case GLUT_KEY_F1:
        camera.enableThirdCarView();
        camera.thirdCarView(car);
        break;
    case GLUT_KEY_F2:
        camera.disableThirdCarView();
        break;
    }

    glutPostRedisplay();
}

void carMovement(unsigned char key, int x, int y)
{
    Point3D nextCarPosition;
    Quaternion rotationQ;
    Vector3D nextDirection;

    switch (key)
    {
    case 'w':

        if (!camera.isThirdCarView)
        {
            camera.moveForward();
            break;
        }

        nextCarPosition = car.position + car.direction;

        if (isOutOfBounds(nextCarPosition))
            break;

        car.moveFoward();
        camera.moveForward();
        break;
    case 's':
    
        if (!camera.isThirdCarView)
        {
            camera.moveBackward();
            break;
        }
        nextCarPosition = car.position - car.direction;

        if (isOutOfBounds(nextCarPosition))
            break;

        car.moveBackward();
        camera.moveBackward();
        break;
    case 'a':

        if (!camera.isThirdCarView)
        {
            camera.moveLeft();
            break;
        }

        rotationQ = Quaternion(20, car.upVector);
        rotationQ.normalize();

        nextDirection = rotationQ.rotate(car.direction);
        nextDirection.normalize();

        nextCarPosition = car.position + nextDirection;

        if (isOutOfBounds(nextCarPosition))
            break;

        car.moveLeft();
        camera.moveLeft();
        break;
    case 'd':

        if (!camera.isThirdCarView)
        {
            camera.moveRight();
            break;
        }

        rotationQ = Quaternion(-20, car.upVector);
        rotationQ.normalize();

        nextDirection = rotationQ.rotate(car.direction);
        nextDirection.normalize();

        nextCarPosition = car.position + nextDirection;

        if (isOutOfBounds(nextCarPosition))
            break;

        car.moveRight();
        camera.moveRight();
        break;
    case ' ':
        camera.moveUp();
        break;
    case 'z':
        camera.moveDown();
        break;
    }

    if (key == 'w' || key == 's' || key == 'a' || key == 'd')
    {
        camera.thirdCarView(car);
    }

    glutPostRedisplay();
}