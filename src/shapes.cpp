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
        glutSolidSphere(_radius, 30, 30);
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

        glBegin(GL_QUADS);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, _size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, _size/2);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(0, _size*sqrt(3)/4, -_size/2);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(0, _size*sqrt(3)/4, _size/2);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, _size/2);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, _size/2);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(-_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(_size/2, -_size*sqrt(3)/4, -_size/2);
            glVertex3f(0, _size*sqrt(3)/4, -_size/2);
        glEnd();

    glPopMatrix();
}

void Cylinder::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glShadeModel(GL_SMOOTH); // da bi sve tačke bile iste boje

        double i,j;

        /* Iscrtava se omot cilindra */
        for (i = -_height/2; i < _height/2; i += _height / 20)
        {
            glBegin(GL_TRIANGLE_STRIP);
                for (j = 0; j <= M_PI * 2 + 0.01; j += M_PI / 20)
                {
                    glNormal3f(cos(j), 0, sin(j));
                    glVertex3f(cos(j)*_base, i, sin(j)*_base);

                    glNormal3f(cos(j), 0, sin(j));
                    glVertex3f(cos(j)*_base, i+_height/20, sin(j)*_base);
                }
            glEnd();
        }

        /* Iscrtavaju se baze cilindra */
        for (i = -_height/2; i <= _height/2; i += _height)
        {
            glBegin(GL_TRIANGLE_FAN);
                glVertex3f(0, i, 0);
                for (j = 0; j <= 360; j++)
                {
                    glVertex3f(cos(j)*_base, i, sin(j)*_base);
                }
            glEnd();
        }
    glPopMatrix();
}
