#include "shapes.hpp"
#include "mainCube.hpp"
#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Sphere::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glutSolidSphere(_size, 30, 30);
    glPopMatrix();
}

void Cube::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        glutSolidCube(_size);
    glPopMatrix();
}

void TriangularPrism::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        draw_prism(_size);
    glPopMatrix();
}

void Cylinder::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);
        draw_cylinder(_height, _size, false);
    glPopMatrix();
}

/* Zvezda se crta iz 12 trostranih prizmi, sa leva na desno po redovima */
void Star::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);

        glPushMatrix();
            glTranslatef(0, 0, -_size*sqrt(3)/4*3);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/2, 0, -_size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/2, 0, -_size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/2, 0, _size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/2, 0, _size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, _size*sqrt(3)/4*3);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

    glPopMatrix();
}

/* Srce se crta iz tri dela, trostrane prizme i dva poluvaljka */
void Heart::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);

        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            draw_prism(_size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/4, 0, -_size*sqrt(3)/4);
            glRotatef(180, 0, 1, 0);
            draw_cylinder(_size, _size/4, true);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/4, 0, -_size*sqrt(3)/4);
            glRotatef(180, 0, 1, 0);
            draw_cylinder(_size, _size/4, true);
        glPopMatrix();

    glPopMatrix();
}

/* Cvet se crta iz nekoliko delova, 5 valjaka koji predtavljaju latice i dva kruga koji predstavljaju sredinu cveta */
void Flower::draw() const
{
    glColor3f(_color_r, _color_g, _color_b);

    glPushMatrix();
        glTranslatef(_center_x, _center_y, _center_z);

        glPushMatrix();
            glTranslatef(0, 0, -_size*7/6);
            draw_cylinder(_size, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size*7/6, 0, 0);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size*7/6, 0, 0);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/2, 0, _size);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/2, 0, _size);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glColor3f(1, 1, 0);
        draw_base(_size+0.01, _size*2/3, false);
    glPopMatrix();
}

/* Trostrana prizma crta se od dva trougla medjusobno spojenih pravougaonicima */
void draw_prism(float size)
{
    glBegin(GL_TRIANGLES);
        glVertex3f(-size/2, -size*sqrt(3)/4, size/2);
        glVertex3f(size/2, -size*sqrt(3)/4, size/2);
        glVertex3f(0, size*sqrt(3)/4, size/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(0, size*sqrt(3)/4, -size/2);
        glVertex3f(0, size*sqrt(3)/4, size/2);
        glVertex3f(size/2, -size*sqrt(3)/4, size/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0, size*sqrt(3)/4, -size/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, size/2);
        glVertex3f(0, size*sqrt(3)/4, size/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(size/2, -size*sqrt(3)/4, size/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, size/2);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(-size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -size/2);
        glVertex3f(0, size*sqrt(3)/4, -size/2);
    glEnd();
}

/* half parametar oznacava da li se iscrtava ceo ili polovina cilindra*/
void draw_cylinder(float height, float base, bool half)
{
    glShadeModel(GL_SMOOTH); // da bi sve tačke bile iste boje

    double i,j;
    int h = 2;

    if(half)
       h = 1;

    /* Iscrtava se omot cilindra */
    for(i = -height/2; i < height/2; i += height / 20)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(j = 0; j <= M_PI*h + 0.01; j += M_PI / 20)
        {
            glNormal3f(cos(j), 0, sin(j));
            glVertex3f(cos(j)*base, i, sin(j)*base);

            glNormal3f(cos(j), 0, sin(j));
            glVertex3f(cos(j)*base, i+height/20, sin(j)*base);
        }

        glEnd();
    }

    draw_base(height, base, half);
}

/* Iscrtavaju se baze cilindra */
void draw_base(float height, float base, bool half)
{
    double i,j;

    for(i = -height/2; i <= height/2; i += height)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, i, 0);
        for(j = 0; j <= 365; j++)
        {
            if(sin(j) < 0 && half)
            {
                glVertex3f(cos(j)*base, i , -sin(j)*base);
                continue;
            }

            glVertex3f(cos(j)*base, i, sin(j)*base);
        }
        glEnd();
    }
}