#include "numbers.h"

void RenderString(float x, float y, void *font, const unsigned char *str)
{
    glColor3ub(183, 28, 28);
    glRasterPos2f(x, y);
    glutBitmapString(font, str);
}

void drawNumbers()
{
    unsigned char time_1[4] = "1";
    unsigned char time_2[4] = "2";
    unsigned char time_3[4] = "3";
    unsigned char time_4[4] = "4";
    unsigned char time_5[4] = "5";
    unsigned char time_6[4] = "6";
    unsigned char time_7[4] = "7";
    unsigned char time_8[4] = "8";
    unsigned char time_9[4] = "9";
    unsigned char time_10[4] = "10";
    unsigned char time_11[4] = "11";
    unsigned char time_12[4] = "12";

    RenderString(-2, 40, GLUT_BITMAP_TIMES_ROMAN_24, time_12);
    RenderString(0, -40, GLUT_BITMAP_TIMES_ROMAN_24, time_6);
    RenderString(40, 0, GLUT_BITMAP_TIMES_ROMAN_24, time_3);
    RenderString(-40, 0, GLUT_BITMAP_TIMES_ROMAN_24, time_9);

    RenderString(-35, 20, GLUT_BITMAP_TIMES_ROMAN_24, time_10);
    RenderString(35, 20, GLUT_BITMAP_TIMES_ROMAN_24, time_2);
    RenderString(35, -20, GLUT_BITMAP_TIMES_ROMAN_24, time_4);
    RenderString(-35, -20, GLUT_BITMAP_TIMES_ROMAN_24, time_8);

    RenderString(-20, 35, GLUT_BITMAP_TIMES_ROMAN_24, time_11);
    RenderString(20, 35, GLUT_BITMAP_TIMES_ROMAN_24, time_1);
    RenderString(20, -35, GLUT_BITMAP_TIMES_ROMAN_24, time_5);
    RenderString(-20, -35, GLUT_BITMAP_TIMES_ROMAN_24, time_7);
}
