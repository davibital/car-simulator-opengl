#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "terrain/terrainData.cpp"
#include "../headers/Camera.hpp"

using namespace std;

vector<vector<int>> terrainMatrix;
int terrainWidth, terrainLength;
int maxTerrainHeight;

Camera camera;

void init();
void display();
void reshape(int w, int h);

void initTerrain();

void drawTerrainMesh();

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