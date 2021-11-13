#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void printGLText(void)
{
    // http: //www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
}

static void drawWatch(void)
{
    const double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double angle = time * 90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0);

    glPushMatrix();
    glTranslated(0, 1, -8);
    gluDisk(gluNewQuadric(), 0, 1, 12, stacks);

    glPushMatrix();
    glTranslated(0, -0.12, 1);
    glColor3d(0, 1, 0);
    gluPartialDisk(gluNewQuadric(), 0, 0.9, 12, stacks, 0, angle / 4); // Seria legal para as horas
    glPopMatrix();

    glPopMatrix();
}

static void display(void)
{
    drawWatch();
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
