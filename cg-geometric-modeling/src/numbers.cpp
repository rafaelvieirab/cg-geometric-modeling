#include "numbers.h"

void drawNumber(float posX, float posY, const unsigned char *number)
{
    glColor3ub(255, 255, 255);
    glRasterPos2f(posX, posY);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, number);
}

void drawNumbers()
{

    unsigned char number_1[4] = "1";
    unsigned char number_2[4] = "2";
    unsigned char number_3[4] = "3";
    unsigned char number_4[4] = "4";
    unsigned char number_5[4] = "5";
    unsigned char number_6[4] = "6";
    unsigned char number_7[4] = "7";
    unsigned char number_8[4] = "8";
    unsigned char number_9[4] = "9";
    unsigned char number_10[4] = "10";
    unsigned char number_11[4] = "11";
    unsigned char number_12[4] = "12";

    drawNumber(20, 35, number_1);
    drawNumber(35, 20, number_2);
    drawNumber(40, 0, number_3);
    drawNumber(35, -20, number_4);
    drawNumber(20, -35, number_5);
    drawNumber(0, -40, number_6);
    drawNumber(-20, -35, number_7);
    drawNumber(-35, -20, number_8);
    drawNumber(-40, 0, number_9);
    drawNumber(-35, 20, number_10);
    drawNumber(-20, 35, number_11);
    drawNumber(-2, 40, number_12);
}
