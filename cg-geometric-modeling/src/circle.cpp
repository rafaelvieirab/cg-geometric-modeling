#include <GL/gl.h>
#include <math.h>
#include "circle.h"

void circle(GLfloat xc, GLfloat yc, GLfloat raio, bool fill)
{
    const GLfloat c = 3.14169f / 180.0f;
    GLint i;

    glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);

    for (i = 0; i <= 360; i += 2)
    {
        float a = i * c;
        glVertex2f(xc + sin(a) * raio, yc + cos(a) * raio);
    }

    glEnd();
}
