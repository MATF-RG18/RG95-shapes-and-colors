#include "mainCube.hpp"
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>

void MainCube::draw() const
{
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glRotatef(30, 0, 1, 0);
        glutWireCube(_size);
    glPopMatrix();
}

float MainCube::getSize() const
{
    return _size;
}