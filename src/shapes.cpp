#include "shapes.hpp"
#include "mainCube.hpp"
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Sphere::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glutWireSphere(_radius, 10, 10);
    glPopMatrix();
}

void Cube::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glutWireCube(_size);
    glPopMatrix();
}

void TriangularPrism::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glBegin(GL_TRIANGLES);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(0, _size*sqrt(3)/4, _size/2);
        glEnd();

        glBegin(GL_QUAD_STRIP);
            glVertex3f(_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, _size/2);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, -_size/2);
        glEnd();

    glPopMatrix();
}