//
//  materials.cpp
//  projCG
//
//  Created by Francisco Carreira on 08/12/2021.
//

#include "materials.h"
#include <GLUT/Glut.h>

/*
    List of materials

    0: BlackPlastic
    1: GrayPlastic
    2: RedPlastic
    3: WhitePlastic
    4: Silver
*/

void initMaterial(int material) {
    switch (material) {
    case 0:
        glMaterialfv(GL_FRONT, GL_AMBIENT, BlackPlastic.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, BlackPlastic.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, BlackPlastic.specular);
        glMaterialf(GL_FRONT, GL_SHININESS, BlackPlastic.shininess);
        break;
    case 1:
        glMaterialfv(GL_FRONT, GL_AMBIENT, GrayPlastic.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, GrayPlastic.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, GrayPlastic.specular);
        glMaterialf(GL_FRONT, GL_SHININESS, GrayPlastic.shininess);
        break;
    case 2:
        glMaterialfv(GL_FRONT, GL_AMBIENT, RedPlastic.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, RedPlastic.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, RedPlastic.specular);
        glMaterialf(GL_FRONT, GL_SHININESS, RedPlastic.shininess);
        break;
    case 3:
        glMaterialfv(GL_FRONT, GL_AMBIENT, WhitePlastic.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, WhitePlastic.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, WhitePlastic.specular);
        glMaterialf(GL_FRONT, GL_SHININESS, WhitePlastic.shininess);
        break;
    case 4:
        glMaterialfv(GL_FRONT, GL_AMBIENT, Silver.ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, Silver.diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, Silver.specular);
        glMaterialf(GL_FRONT, GL_SHININESS, Silver.shininess);
        break;
    }
}
