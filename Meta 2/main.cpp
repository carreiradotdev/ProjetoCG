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
#include "textures.h"
#include "lights.h"
#include "materials.h"

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
GLfloat   rVisao = 5, aVisao = 0.25 * PI, incVisao = 0.05, disty = 3, play = 0;
GLint      dim = 64;

GLfloat   aVisao2 = -0.75 * PI;
GLdouble  obsV[] = {centerx, centery, centerz};
GLdouble  obsP[] = {centerx + rVisao * cos(aVisao), centery + disty, centerz + rVisao * sin(aVisao)};
GLint choice = 0;
GLint i = 0, j = 0;
GLfloat Px = 8.0, Py = 3.0, Pz = 9.0;
GLdouble  obsV2[] = {Px + rVisao * cos(aVisao2), 2.0, Pz + rVisao * sin(aVisao2)};
GLdouble  obsP2[] = {Px, Py, Pz};

GLfloat  angZoom = 45, incZoom = 2;
GLfloat  ty1 = 0.3, ty2 = 0.3, ty3 = 0.3, incAlt = -0.01, rot2 = -2;
GLfloat	 objrotx = 45, objroty = 45;
GLint	 press1 = 0, press2 = 0, press0 = 0, on_off = 0, rotationMode = 0;
GLint	 msec = 10;
GLfloat playR = 0.60, playB = 0.60, playG = 0.70;
// Sky Box
GLUquadric* skyBox = gluNewQuadric();
GLint count = 0;
GLint directionON = 0;
GLint spotON = 0;

static GLuint     baseFront[]     = {0, 1, 2, 3};
static GLuint     baseRight[]     = {4, 5, 6, 7};
static GLuint     baseUp[]        = {8, 9, 10, 11};
static GLuint     baseBack[]      = {12, 13, 14, 15};
static GLuint     baseLeft[]      = {16, 17, 18, 19};
static GLuint     baseDown[]      = {20, 21, 22, 23};

void init(void) {
    glClearColor(BLACK);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    initTextures();
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    initLights();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);

    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normal);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glTexCoordPointer(2, GL_FLOAT, 0, textures);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
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

void drawObservator(int choice) {
    if (choice) {
        glPushMatrix(); {
            //changeColor(0.76, 0.88, 0.97);
            glTranslated(obsP2[0], obsP2[1], obsP2[2]);
            glScaled(0.5, 1.0, 0.5);
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseUp);
        }glPopMatrix();
        glPushMatrix(); {
            glTranslated(obsP2[0], obsP2[1], obsP2[2]);
            glRotated(0.5 * -aVisao2 * 360 / PI, 0.0, 1.0, 0.0);
            glTranslated(0.4, 0.0, 0.0);
            glScaled(0.8, 1.0, 0.1);
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseUp);
        }glPopMatrix();
    }
    else {
        //================================================================= Desenho do observador do mini-mapa
        glPushMatrix(); {
            //changeColor(0.76, 0.88, 0.97);
            glTranslated(obsP[0], obsP[1], obsP[2]);
            glScaled(0.5, 1.0, 0.5);
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baseUp);

        }glPopMatrix();
    }

}

void drawScene() {
    static GLUquadric* gluQuadric = NULL;
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    initLights();
    
    if (rotationMode) {
        objroty = objroty + 1;
    }
    
    if (press1) {
        ty1 = ty1 - 1;
        if (ty1 < -10) { press1 = 0; ty1 = 0; }
    }
    
    if (press2) {
        ty2 = ty2 + incAlt;
        if (ty2 < 0.22) { incAlt = -incAlt; }
        if (ty2 > 0.3) { incAlt = -incAlt; press2 = 0; }
    }
    
    glPushMatrix(); {
        glTranslated(0.0, -10, 0.0);
        glScaled(5, 5, 5);
        glTranslatef(-1.0, 0, -1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ipodObj);
        
        glBegin(GL_QUADS);
        float med_dim = (float)dim / 2;
        for (i = 0; i < dim; i++)
            for (j = 0; j < dim; j++) {
                glTexCoord2f((float)j / dim, (float)i / dim);
                glVertex3d((float)i / med_dim, 0, (float)j / med_dim);
                
                glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
                glVertex3d((float)i / med_dim, 0, (float)(j + 1) / med_dim);
                
                glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
                glVertex3d((float)(i + 1) / med_dim, 0, (float)(j + 1) / med_dim);
                
                glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
                glVertex3d((float)(i + 1) / med_dim, 0,(float)j / med_dim);
            } glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
    } glPopMatrix();
    
    glTranslatef(centerx, centery, centerz);
    glRotatef(objroty, 0.0, 1.0, 0.0);
    glRotatef(objrotx, 1.0, 0.0, 0.0);
    
    initMaterial(1);
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
    
    initMaterial(2);
    glPushMatrix();
        glTranslated(0.0, 0.25, 0.75);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
            glRotated(ty1, 0, 0, 1);
            glScalef(1, 1, 0.3);
            glTranslatef(0, -size/2+0.25, size-0.45);
            glutWireTorus(0.2,0.5,30,30);
        glPopMatrix();
        glFlush();
    glPopMatrix();
    
    //======================================================== OK BUTTON
    
    glEnable(GL_BLEND);
    glPushMatrix();
    
    glTranslatef(0,ty2-0.25, size+0.25);
    glScalef(2, 2, 2);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    
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
    glDisable(GL_BLEND);
    
    glPushMatrix(); {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,screenObj);
        glTranslated(0.0, 0.26, -0.65);
        glScaled(1.5, 1.0, 1.3);
        glColor3f(0.60, 0.60, 0.70);
        glNormal3d(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON); {
            glTexCoord2f(0.0f,0.0f); glVertex3d(-size, 0.0, -size);
            glTexCoord2f(0.0f,1.0f); glVertex3d(-size, 0.0, size);
            glTexCoord2f(1.0f,1.0f); glVertex3d(size, 0.0, size);
            glTexCoord2f(1.0f,0.0f); glVertex3d(size, 0.0, -size);
        }glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
    } glPopMatrix();
    
}

void initLights(void) {
    
    for (int i = 0; i < 3; i++) {
        spotLight.ambient[i] = spotLight.color[i] * spotLight.intensity * spotON;
        spotLight.diffuse[i] = spotLight.color[i] * spotLight.intensity * spotON;
        spotLight.specular[i] = spotLight.color[i] * spotLight.intensity * spotON;
        directionLight.ambient[i] = directionLight.color[i] * directionLight.intensity * directionON;
        directionLight.diffuse[i] = directionLight.color[i] * directionLight.intensity * directionON;
        directionLight.specular[i] = directionLight.color[i] * directionLight.intensity * directionON;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, spotLight.position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, spotLight.ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spotLight.diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spotLight.specular);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotLight.direction);
    glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spotLight.exponent);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spotLight.cutoff);

    glLightfv(GL_LIGHT1, GL_POSITION, directionLight.position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, directionLight.ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, directionLight.diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, directionLight.specular);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    initTextures();
    glViewport(500, 400, wScreen-500, hScreen-400);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], obsV[0], obsV[1], obsV[2], 0, 1, 0);
    choice = 0;
    
    drawAxis();
    drawScene();
    
    glViewport(0, 0, 500, 400);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -10, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 9, 0, 0, 0, 0, 0, 0, -1);
    drawAxis();
    drawScene();
    
    glutSwapBuffers();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
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
            rVisao = rVisao + 1;
            break;
            
        case 'L':
        case 'l':
            if (rVisao > 2) { rVisao = rVisao - 1; }
            break;
        
        case '9':
            spotON = !spotON;
            if (spotON) {
                glEnable(GL_LIGHT0);
            }
            else {
                glDisable(GL_LIGHT0);
            }
            break;
            
        case '8':
            directionON = !directionON;
            if (directionON) {
                glEnable(GL_LIGHT1);
            }
            else {
                glDisable(GL_LIGHT1);
            }
            break;
            
        case '7':
            directionLight.color[0] -= 0.5;
            break;
            
        case '6':
            directionLight.color[1] -= 0.5;
            break;
            
        case '5':
            directionLight.color[2] -= 0.5;
            break;
        case '0':
            RedPlastic.shininess += 0.1 * 128;
            break;
            
        case 27:
            gluDeleteQuadric(skyBox);
            exit(0);
            break;
    }
    
    obsP[0] = centerx + rVisao * cos(aVisao);
    obsP[1] = centery + disty;
    obsP[2] = centerz + rVisao * sin(aVisao);

    obsP2[0] = Px;
    obsP2[2] = Pz;
    obsV2[0] = Px + rVisao * cos(aVisao2);
    obsV2[2] = Pz + rVisao * sin(aVisao2);

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
        aVisao = aVisao + incVisao;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_RIGHT) {
        aVisao = aVisao - incVisao;
        glutPostRedisplay();
        
    }
    obsP[0] = centerx + rVisao * cos(aVisao);
    obsP[1] = centery + disty;
    obsP[2] = centerz + rVisao * sin(aVisao);
    
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
    glutTimerFunc(msec, Timer, 1);
    
    glutMainLoop();
    
    return 0;
}
