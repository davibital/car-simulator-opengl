#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <stdio.h>

#include "terrainData.cpp"

using namespace std;

vector<vector<int>> terrainMatrix;
int terrainWidth, terrainHeight;

void init();
void display();
void reshape(int w, int h);

void initTerrain();

// TODO: Implementar função para desenhar a malha do terreno
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

    gluPerspective(60.0, 1.0, 0.5, 100.0);

    gluLookAt(terrainWidth * 1.75, terrainHeight * 1.75, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, terrainHeight, 0.0);
        glVertex3f(terrainWidth, terrainHeight, 0.0);
        glVertex3f(terrainWidth, 0.0, 0.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void initTerrain()
{
    terrainWidth = getTerrainWidth();
    terrainHeight = getTerrainLength();
    terrainMatrix = getTerrainMatrix();
}