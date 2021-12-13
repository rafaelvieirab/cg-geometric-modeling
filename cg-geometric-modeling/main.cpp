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

const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

GLfloat xf, yf, win;
GLint view_w, view_h;

GLuint textureId;
std::string images[3] = {"clock.png", "clock1.png", "clock2.png"};
int positionImage = 0;
bool stop = false;
bool clockWithNumbers = false;

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

void drawClockPointers2() {
    glColor3f(0.0f, 0.0f, 0.0f);

    float angle_s = second * 6;
    GLfloat color_s[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_s, color_s, sy, 2);
    glLoadIdentity();

    float angle_m = minute * 6;
    GLfloat color_m[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_m, color_m, my, 2);
    glLoadIdentity();

    float angle_h = (hour + minute / 60.0) * 30;
    GLfloat color_h[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_h, color_h, hy, 2);
    glLoadIdentity();
}

void drawClockWithTexture(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(1, 1, 1);

    drawClockPointers();
    std::string path = "/home/fcoalex/Documentos/Desenvolvimento/cg/cg-geometric-modeling/cg-geometric-modeling/" + images[positionImage];
    char* filepath = (char*) path.c_str();
    textureId = drawTexture(filepath, xf, yf);

    glFlush();
}

void drawClockWithNumbers(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(153, 0, 51);

    circle(0, 0, 48.0f);
    drawNumbers();
    drawClockPointers2();

    glFlush();
}

void draw(void) {
    if(clockWithNumbers) {
        drawClockWithNumbers();
    } else {
        drawClockWithTexture();
    }
}

void resizeFunc(GLsizei width, GLsizei height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(clockWithNumbers) {
        if (width <= height)
            gluOrtho2D(-tam_x, tam_x, -tam_y * height / width, tam_y * height / width);
        else
            gluOrtho2D(-tam_x * width / height, tam_x * width / height, -tam_y, tam_y);
    } else
        gluOrtho2D(-win, win, -win, win);

    glMatrixMode(GL_MODELVIEW);
}

void moveFunc(int n)
{
    if(!stop) {
        time_t currentTime = time(0);
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
        case 'z':
        case 'Z':
            stop = false;
            glutTimerFunc(1000, moveFunc, 0);
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    glutCreateWindow("Clock");
    glutDisplayFunc(draw);
    glutReshapeFunc(resizeFunc);
    glutKeyboardFunc(keyBoardFunc);
    glutTimerFunc(1000, moveFunc, 0);

    initialize();
    glutMainLoop();

    return 0;
}
