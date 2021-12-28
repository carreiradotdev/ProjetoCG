//
//  materials.hpp
//  projCG
//
//  Created by Francisco Carreira on 08/12/2021.
//

#ifndef materials_h
#define materials_h

#include <stdio.h>
#include <GLUT/Glut.h>

void initMaterial(int);

struct {
    GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
    GLfloat diffuse[3] = { 0.01, 0.01, 0.01 };
    GLfloat specular[3] = { 0.5, 0.5, 0.5 };
    GLfloat shininess = 0.25 * 128;
} BlackPlastic;

struct {
    GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
    GLfloat diffuse[3] = { 0.2, 0.2, 0.2 };
    GLfloat specular[3] = { 0.55, 0.55, 0.55 };
    GLfloat shininess = 0.25 * 128;
} GrayPlastic;

struct {
    GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
    GLfloat diffuse[3] = { 0.5, 0.0, 0.0 };
    GLfloat specular[3] = { 0.7, 0.6, 0.6 };
    GLfloat shininess = 0.25 * 128;
} RedPlastic;

struct {
    GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
    GLfloat diffuse[3] = { 0.55, 0.55, 0.55 };
    GLfloat specular[3] = { 0.7, 0.7, 0.7 };
    GLfloat shininess = 0.25 * 128;
} WhitePlastic;

struct {
    GLfloat ambient[3] = { 0.19225, 0.19225, 0.19225 };
    GLfloat diffuse[3] = { 0.50754, 0.50754, 0.50754 };
    GLfloat specular[3] = { 0.508273, 0.508273, 0.508273 };
    GLfloat shininess = 0.4 * 128;
} Silver;

#endif /* materials_h */
