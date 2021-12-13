#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string>
#include <cstring>
#include "circle.h"
#include "numbers.h"

const GLfloat tam_x = 90.0f;
const GLfloat tam_y = 90.0f;

const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

int hour;
int minute;
int second;

void drawClockPointer(float angle, GLfloat *color, GLint posY)
{
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(color[0], color[1], color[2]);
    glVertex2i(0, 0);
    glVertex2i(0, posY);
    glEnd();
}


void drawClockPointers() {
    glColor3f(0.0f, 0.0f, 0.0f);

    float angle_s = second * 6;
    GLfloat color_s[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_s, color_s, sy);
    glLoadIdentity();

    float angle_m = minute * 6;
    GLfloat color_m[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_m, color_m, my);
    glLoadIdentity();

    float angle_h = (hour + minute / 60.0) * 30;
    GLfloat color_h[3] = {255.0f, 255.0f, 255.0f};
    drawClockPointer(angle_h, color_h, hy);
    glLoadIdentity();
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(153, 0, 51);

    circle(0, 0, 48.0f, true);
    drawNumbers();
    drawClockPointers();

    glFlush();
}



void resize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height)
        gluOrtho2D(-tam_x, tam_x, -tam_y * height / width, tam_y * height / width);
    else
        gluOrtho2D(-tam_x * width / height, tam_x * width / height, -tam_y, tam_y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void move(int n)
{
    // time_t currentTime = time(NULL);
    time_t currentTime = time(0);
    struct tm *timeInfo = localtime(&currentTime);

    hour = timeInfo->tm_hour;
    minute = timeInfo->tm_min;
    second = timeInfo->tm_sec;

    glutPostRedisplay();
    glutTimerFunc(1000, move, 0);
}

void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    //glutInitWindowPosition(10,10);
    glutCreateWindow("Clock");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutTimerFunc(1000, move, 0);
    initialize();
    glutMainLoop();
    return 0;
}
