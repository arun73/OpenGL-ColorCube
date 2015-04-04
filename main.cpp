#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

typedef GLfloat vec3[3];

vec3 theta = {0, 0, 0};     // 'x', 'y', 'z' keys are used to change axis
GLint axis = 2;
GLfloat ROTATION_SPEED = 1; // 'UP' & 'DOWN' arrow to control speed

vec3 vertices[8] = {
        {-1, -1, -1},
        {1,  -1, -1},
        {1,  1,  -1},
        {-1, 1,  -1},
        {-1, -1, 1},
        {1,  -1, 1},
        {1,  1,  1},
        {-1, 1,  1}
};

vec3 colors[8] = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 1, 1}
};

GLubyte cubeIndices[24] = {
        0, 3, 2, 1,
        2, 3, 7, 6,
        0, 4, 7, 3,
        1, 2, 6, 5,
        4, 5, 6, 7,
        0, 1, 5, 4
};

void display();
void colorCube();
void spinCube();
void reshape(int w, int h);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Color Cube with Vertex Array");
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutKeyboardFunc(processNormalKeys);
    glutReshapeFunc(reshape);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glOrtho(-2, 2, -2, 2, -2, 2);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glRotatef(theta[0], 1, 0, 0);
    glRotatef(theta[1], 0, 1, 0);
    glRotatef(theta[2], 0, 0, 1);
    colorCube();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2, 2, -2 * (GLfloat) h / (GLfloat) w, 2 * (GLfloat) h / (GLfloat) w, -2, 2);
    else
        glOrtho(-2 * (GLfloat) w / (GLfloat) h, 2 * (GLfloat) w / (GLfloat) h, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void spinCube() {
    theta[axis] = (GLfloat) fmod(theta[axis] + ROTATION_SPEED, 360);
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
            axis = 0;
            break;
        case 'y':
            axis = 1;
            break;
        case 'z':
            axis = 2;
            break;
        default:
            break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            ROTATION_SPEED += 0.1;
            break;
        case GLUT_KEY_DOWN:
            ROTATION_SPEED -= 0.1;
            break;
        default:
            break;
    }
}

void colorCube() {
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
}