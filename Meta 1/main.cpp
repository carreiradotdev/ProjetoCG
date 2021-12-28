/* ===================================================================================
 Computacao Grafica - Projeto - 2021/22
 Francisco Carreira - 2019222462
 ======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "vertex.h"
#include "normals.h"
#include "colors.h"

#include <GLUT/glut.h>

#define GL_SILENCE_DEPRECATION 1

//--------------------------------- Definir cores
#define BLUE        0.0, 0.0, 1.0, 1.0
#define BLUE        0.0, 0.0, 1.0, 1.0
#define RED		    1.0, 0.0, 0.0, 1.0
#define YELLOW	    1.0, 1.0, 0.0, 1.0
#define GREEN       0.0, 1.0, 0.0, 1.0
#define WHITE       1.0, 1.0, 1.0, 1.0
#define BLACK       0.0, 0.0, 0.0, 1.0
#define BACKGROUND  0.8, 0.8, 0.8, 1.0

#define PI		 3.14159
 
GLint		wScreen = 800, hScreen = 600;
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;

GLfloat centerx = 0, centery = 0, centerz = 0;
GLfloat   rVision = 5, angVision = 0.25 * PI, decline = 0.03, disty = 3, play = 0;

GLdouble  obsV[] = {centerx, centery, centerz};
GLdouble  obsP[] = {centerx + rVision * cos(angVision), centery + disty, centerz + rVision * sin(angVision)};

GLfloat  angZoom = 45;
GLfloat  ty1 = 0.3, ty2 = 0.3, ty3 = 0.3, incAlt = -0.01;
GLfloat	 objrotx = 45, objroty = 45;
GLboolean	 press1 = 0, press2 = 0, press0 = 0, on_off = 0, rotationMode = 0;
GLint	 msec = 10;
GLfloat playR = 0.60, playB = 0.60, playG = 0.70;

void init(void) {
    glClearColor(BACKGROUND);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normal);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
}

void drawAxis() {
    glColor4f(RED);
    glBegin(GL_LINES); {
        glVertex3i(0, 0, 0);
        glVertex3i(100, 0, 0);
    } glEnd();
    glColor4f(GREEN);
    glBegin(GL_LINES); {
        glVertex3i(0, 0, 0);
        glVertex3i(0, 100, 0);
    } glEnd();
    glColor4f(BLUE);
    glBegin(GL_LINES); {
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 100);
    } glEnd();
}

void drawScene() {
    static GLUquadric* gluQuadric = NULL;
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    if (rotationMode) {
        objroty = objroty + 1;
    }
    
    if (press1) {
        ty1 = ty1 - 1;
        if (ty1 < -10) {
            press1 = 0;
            ty1 = 0;
        }
    }
    
    if (press2) {
        ty2 = ty2 + incAlt;
        if (ty2 < 0.2) {
            incAlt = -incAlt;
        }
        if (ty2 > 0.3) {
            incAlt = -incAlt;
            press2 = 0;
        }
    }
    
    glTranslatef(centerx, centery, centerz);
    glRotatef(objroty, 0.0, 1.0, 0.0);
    glRotatef(objrotx, 1.0, 0.0, 0.0);
    
    static GLuint     baseFront[]     = {0, 1, 2, 3};
    static GLuint     baseRight[]     = {4, 5, 6, 7};
    static GLuint     baseUp[]        = {8, 9, 10, 11};
    static GLuint     baseBack[]      = {12, 13, 14, 15};
    static GLuint     baseLeft[]      = {16, 17, 18, 19};
    static GLuint     baseDown[]      = {20, 21, 22, 23};
    
    glPushMatrix(); {
        glScalef(2, 0.5, 3);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseFront);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseRight);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseUp);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseBack);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseLeft);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseDown);
    }
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.0, 0.25, 0.75);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
            glRotated(ty1, 0, 0, 1);
            glScalef(1, 1, 0.3);
            glTranslatef(0, -size/2+0.25, size-0.45);
            glutSolidTorus(0.2,0.5,30,30);
        glPopMatrix();
        glFlush();
    glPopMatrix();
    
    //======================================================== OK BUTTON
    
    glPushMatrix();
    
    glTranslatef(0,ty2-0.25, size+0.25);
    glScalef(2, 2, 2);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.90, 0.90, 0.90);
    
    if (gluQuadric == NULL)
        gluQuadric = gluNewQuadric();
    gluCylinder(gluQuadric, 0.15, 0.15, 0.15, 20, 20);
    
    glPushMatrix();
    glScalef(1, 1, 0.25);
    glTranslatef(0,0, size+0.1);
    gluDisk(gluQuadric, 0, 0.15, 20, 20);
    glPopMatrix();
    glFlush();
    glPopMatrix();
    
    glPushMatrix();
        glTranslated(0.0, 0.26, -0.65);
        glScaled(1.5, 1.0, 1.3);
        glColor3f(0.60, 0.60, 0.70);
        glNormal3d(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON); {
            glVertex3d(-size, 0.0, -size);
            glVertex3d(-size, 0.0, size);
            glVertex3d(size, 0.0, size);
            glVertex3d(size, 0.0, -size);
        }glEnd();
    glFlush();
    glPopMatrix();
    
    //======================================================== PLAY BUTTON
    
    glPushMatrix();
    glTranslated(0.0, 0.28, -0.65);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(playR, playG, playB);
    glBegin(GL_TRIANGLES); {
        glVertex3f( 0.0f, 0.5f, 0.0f);
        glVertex3f(-0.5f,-0.5f, 0.0f);
        glVertex3f( 0.5f,-0.5f, 0.0f);
    }glEnd();
    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], obsV[0], obsV[1], obsV[2], 0, 1, 0);
    
    drawAxis();
    drawScene();
    
    glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
        case '0':
            play = !play;
            if (play) {
                playB = 0.6;
                playG = 0.6;
                playR = 0.7;
            } else {
                playB = 0;
                playG = 0;
                playR = 0;
            }
            press0 = 1;
            break;
            
        case '1':
            press1 = 1;
            break;
            
        case '2':
            press2 = 1;
            break;
            
        case 'A':
        case 'a':
            centerx = centerx - 1;
            break;
            
        case 'D':
        case 'd':
            centerx = centerx + 1;
            break;
            
        case 'Z':
        case 'z':
            centery = centery + 1;
            break;
            
        case 'X':
        case 'x':
            centery = centery - 1;
            break;
            
        case 'W':
        case 'w':
            centerz = centerz - 1;
            break;
        case 'S':
        case 's':
            centerz = centerz + 1;
            break;
            
        case 'R':
        case 'r':
            objrotx = objrotx + 10;
            break;
            
        case 'F':
        case 'f':
            objrotx = objrotx - 10;
            break;
            
        case 'Q':
        case 'q':
            objroty = objroty - 10;
            break;
            
        case 'E':
        case 'e':
            objroty = objroty + 10;
            break;
            
        case 'T':
        case 't':
            rotationMode = !rotationMode;
            break;
        case 'O':
        case 'o':
            rVision = rVision + 1;
            break;
            
        case 'L':
        case 'l':
            if (rVision > 2) { rVision = rVision - 1; }
            break;
            
            
            //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
    //======================================================== object + observer update
    obsV[0] = centerx;
    obsV[1] = centery;
    obsV[2] = centerz;
    obsP[0] = centerx + rVision * cos(angVision);
    obsP[1] = centery + disty;
    obsP[2] = centerz + rVision * sin(angVision);
    
    glutPostRedisplay();
}


void teclasNotAscii(int key, int x, int y) {
    
    if (key == GLUT_KEY_UP) {
        disty = disty + 1;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_DOWN) {
        disty = disty - 1;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_LEFT) {
        angVision = angVision + decline;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_RIGHT) {
        angVision = angVision - decline;
        glutPostRedisplay();
        
    }
    obsP[0] = centerx + rVision * cos(angVision);
    obsP[1] = centery + disty;
    obsP[2] = centerz + rVision * sin(angVision);
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Ladies and Gentleman, the iPod.");
    
    init();
    
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
