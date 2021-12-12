#include <GL/gl.h>
#include <math.h>
#include "circle.h"

void circle(GLfloat centerX, GLfloat centerY, GLfloat raio)
{
    const GLfloat c = 3.14169f / 180.0f;
    GLint i;

    glBegin(GL_TRIANGLE_FAN);

    for (i = 0; i <= 360; i += 2)
    {
        float a = i * c;
        glVertex2f(centerX + sin(a) * raio, centerY + cos(a) * raio);
    }

    glEnd();
}
