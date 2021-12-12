#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int elbow = 0; //cotovelo
static int arm = 0;
static int armZ = 0;
static int fingers = 0;
static int flang = 0;

double eye[] = {0, 0, 2};
double center[] = {0, 0, 1};
double up[] = {0, 1, 0};
double speed = 0.2;

int pressed = 0;
int limitForwardBackward = 0;
int limitUpDown = 0;
int limitRightLeft = 0;

int moving, startx, starty;

GLfloat angle = 0.0;  /* in degrees */
GLfloat angle2 = 0.0; /* in degrees */

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void drawHead()
{
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glColor3f(0.71, 0.4, 0.12);
    glutSolidSphere(0.35, 16, 16);
    glPopMatrix();
}

void drawFinger(float translateY, float translateZ, float flang, float finger)
{
    glPushMatrix();

    glTranslatef(-0.475, translateY, translateZ);
    glColor3f(1, 0, 0);

    glTranslatef(0.1, 0, 0);
    glRotatef(flang, 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(finger, 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void drawFingers()
{
    float dfingers[5][4] = {
        {0.05, 0.1125, flang, fingers},
        {0.05, 0.0375, flang, fingers},
        {0.05, -0.0375, flang, fingers},
        {0.05, -0.1125, flang, fingers},
        {-0.1, 0, -flang, -fingers}};

    for (int i = 0; i < 5; i++)
        drawFinger(dfingers[i][0], dfingers[i][1], dfingers[i][2], dfingers[i][3]);
}

void drawArm()
{
    glPushMatrix();

    glTranslatef(-1.25, 1.85, 0.3);
    glRotatef((GLfloat)armZ, 1.0, 0.0, 0.0);
    glTranslatef(0.375, 0, 0);
    glRotatef(arm, 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0);

    // Draw the limb
    // The shoulder is centered in origin and has 1, 1, 1 dimensions
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(0.75, 0.3, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    glTranslatef(-0.75, 0, 0);

    glTranslatef(0.375, 0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0.0);
    glPushMatrix();
    glColor4f(0.71, 0.4, 0.12, 0.5);
    glScalef(0.75, 0.3, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    drawFingers();

    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    drawHead();
    drawArm();

    glPopMatrix();
    glutSwapBuffers();
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{
    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void Left()
{
    // implement camera rotation arround vertical window screen axis to the left
    // used by mouse and left arrow
    rotatePoint(up, (float)22 / 7 / 20, eye);
    limitRightLeft += 1;
}

void Right()
{
    // implement camera rotation arround vertical window screen axis to the right
    // used by mouse and right arrow
    rotatePoint(up, -(float)22 / 7 / 20, eye);
    limitRightLeft -= 1;
}

void Up()
{
    // implement camera rotation arround horizontal window screen axis +ve
    // used by up arrow
    double horizontal[] = {0, 0, 0};

    crossProduct(eye, up, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, 3.14 / 20, eye);
    rotatePoint(horizontal, 3.14 / 20, up);
    limitUpDown += 1;
}

void Down()
{
    // implement camera rotation arround horizontal window screen axis
    // used by down arrow
    double horizontal[] = {0, 0, 0};
    crossProduct(eye, up, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -3.14 / 20, eye);
    rotatePoint(horizontal, -3.14 / 20, up);
    limitUpDown -= 1;
}

void moveForward()
{
    double direction[] = {0, 0, 0};
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;
    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;

    limitForwardBackward += 1;
}

void moveBack()
{
    double direction[] = {0, 0, 0};
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];

    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;
    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;

    limitForwardBackward -= 1;
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (pressed == 0)
        {
            if (limitForwardBackward < 10)
            {
                moveForward();
            }
        }
        else
        {
            if (limitRightLeft < 10)
            {
                Left();
            }
        }
        break;
    case GLUT_KEY_RIGHT:
        if (pressed == 0)
        {
            if (limitForwardBackward > -10)
            {
                moveBack();
            }
        }
        else
        {
            if (limitRightLeft > -10)
            {
                Right();
            }
        }
        break;
    case GLUT_KEY_UP:
        if (limitUpDown < 8)
        {
            Up();
        }
        break;
    case GLUT_KEY_DOWN:
        if (limitUpDown > -8)
        {
            Down();
        }
        break;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // ARMS
    case 'c':
        if (arm < 90)
            arm = (arm + 5) % 360;
        break;

    case 'C':
        if (arm > -90)
            arm = (arm - 5) % 360;
        break;

        // ELBOWS MOVEMENT
    case 'v':
        if (elbow < 130)
            elbow = (elbow + 5) % 360;
        break;

    case 'V':
        if (elbow > -120)
            elbow = (elbow - 5) % 360;
        break;

    case 'D':
        if (armZ < 90)
            armZ = (armZ + 5) % 360;
        break;

    case 'd':
        if (armZ > -90)
            armZ = (armZ - 5) % 360;
        break;

    //FLANG
    case 'q':
        if (flang < 20)
            flang = (flang + 5) % 360;
        break;

    case 'Q':
        if (flang > -20)
            flang = (flang - 5) % 360;
        break;

    // FINGERS
    case 'w':
        if (fingers < 20)
            fingers = (fingers + 5) % 360;
        break;

    case 'W':
        if (fingers > -20)
            fingers = (fingers - 5) % 360;
        break;

    case 'r':
    case 'R':
        reset();
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void reset()
{
    eye[0] = 0;
    eye[1] = 0;
    eye[2] = 2;
    center[0] = 0;
    center[1] = 0;
    center[2] = 1;
    up[0] = 0;
    up[1] = 1;
    up[2] = 0;
    angle = 0;
    angle2 = 0;
    limitRightLeft = 0;
    limitForwardBackward = 0;
    limitUpDown = 0;
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            pressed = 1;
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP)
        {
            moving = 0;
            pressed = 0;
        }
    }
}

static void motion(int x, int y)
{
    if (moving)
    {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();

    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}
