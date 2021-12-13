#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <string>
#include "circle.h"
#include "numbers.h"
#include <SOIL/SOIL.h>
#include "texture.h"
#include <stdlib.h>

const GLfloat tam_x = 50.0f;
const GLfloat tam_y = 50.0f;

const GLfloat second_diff = 0.1f;
const GLfloat minute_diff = 0.6f;
const GLfloat hour_diff = 0.4f;

int hour;
int minute;
int second;

GLfloat xf, yf, win;
GLint view_w, view_h;

GLuint textureId;
std::string images[3] = {"clock.png", "clock1.png", "clock2.png"};
int positionImage = 0;
bool stop = false;

void keyBoardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            xf = xf + 0.1;
            yf = yf + 0.1;
            break;
        case 's':
        case 'S':
            xf = xf - 0.1;
            yf = yf - 0.1;
            break;
        case '1':
            positionImage = 0;
            glDeleteTextures(1, &textureId);
            break;
        case '2':
            positionImage = 1;
            glDeleteTextures(1, &textureId);
            break;
        case '3':
            positionImage = 2;
            glDeleteTextures(1, &textureId);
            break;
        case 'x':
        case 'X':
            stop = true;
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
//    if (button == GLUT_LEFT_BUTTON)
//         if (state == GLUT_DOWN) {
//                  xf = ((2*win* x) / view_w) - win;
//                  yf = (((2*win) * (y-view_h) ) / -view_h) - win;
//         }
//    glutPostRedisplay();
}

void drawClockPointer(float angle, GLfloat *color, GLfloat posY, GLfloat thickness)
{
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);

    circle(0, 0, 0.035);

    glLineWidth(thickness);
    glBegin(GL_LINES);
        glColor3f(color[0], color[1], color[2]);
        glVertex2f(0, 0);
        glVertex2f(0.0, posY);
    glEnd();
}


void drawClockPointers()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    float angle_s = second * 6;
    GLfloat color_s[3] = {1.0f, 0.0f, 0.0f};
    drawClockPointer(angle_s, color_s, yf - second_diff, 1.6);
    glLoadIdentity();

    float angle_m = minute * 6;
    GLfloat color_m[3] = {0.0f, 0.0f, 0.0f};
    drawClockPointer(angle_m, color_m, yf - minute_diff, 4);
    glLoadIdentity();

    float angle_h = (hour + minute / 60.0) * 30;
    GLfloat color_h[3] = {0.0f, 0.0f, 0.0f};
    drawClockPointer(angle_h, color_h, yf - hour_diff, 4);
    glLoadIdentity();
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(1, 1, 1);

    //circle(0, 0, tam_x, true);
    //glColor3ub(0, 0, 0);
    //circle(0, 0, tam_x, false);
    //drawNumbers();
    drawClockPointers();
    std::string path = "/home/fcoalex/Documentos/Desenvolvimento/cg/cg-geometric-modeling/cg-geometric-modeling/" + images[positionImage];
    char* filepath = (char*) path.c_str();
    textureId = drawTexture(filepath, xf, yf);

    glFlush();
}

void resizeFunc(GLsizei width, GLsizei height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    view_w = width;
    view_h = height;

    gluOrtho2D(-win, win, -win, win);

    glMatrixMode(GL_MODELVIEW);
}

void moveFunc(int n)
{
    if(!stop) {
        time_t currentTime = time(NULL);
        struct tm *timeInfo = localtime(&currentTime);

        hour = timeInfo->tm_hour;
        minute = timeInfo->tm_min;
        second = timeInfo->tm_sec;

        glutPostRedisplay();
        glutTimerFunc(1000, moveFunc, 0);
    }
}

void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win=2.0f;
    xf=1;
    yf=1;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    glutCreateWindow("Clock");
    glutDisplayFunc(draw);
    glutReshapeFunc(resizeFunc);
    glutKeyboardFunc(keyBoardFunc);
    glutTimerFunc(1000, moveFunc, 0);
    glutMouseFunc(mouseFunc);

    initialize();
    glutMainLoop();

    return 0;
}
