#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/freeglut.h>

//void drawTexture(char* file);
GLint drawTexture(char* filepath, GLfloat x, GLfloat y);
void deleteTexture(GLuint textureId);

#endif // TEXTURE_H_INCLUDED
