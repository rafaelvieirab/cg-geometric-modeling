#include "texture.h"
#include <SOIL/SOIL.h>
#include <iostream>

void drawTexture(char* filepath, GLfloat x, GLfloat y) {

    GLuint textureId = SOIL_load_OGL_texture(
                           filepath,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (filepath == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(-x, -y);

        glTexCoord2f(1, 0);
        glVertex2f(x, -y);

        glTexCoord2f(1, 1);
        glVertex2f(x, y);

        glTexCoord2f(0, 1);
        glVertex2f(-x, y);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}
