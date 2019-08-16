#include "shapes.hpp"
#include "mainCube.hpp"
#include <cmath>

unsigned int Shape::id = 0;

void Sphere::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        glutSolidSphere(_size, 30, 30);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

void Cube::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        glutSolidCube(_size);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void TriangularPrism::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        draw_prism(_size, _height);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void Cylinder::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        draw_cylinder(_height, _size, false);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

/* Zvezda se crta iz 12 trostranih prizmi, sa leva na desno po redovima */
void Star::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);

        glPushMatrix();
            glTranslatef(0, 0, -_size*sqrt(3)/4*3);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/2, 0, -_size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/2, 0, -_size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size, 0, -_size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/2, 0, _size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/2, 0, _size*sqrt(3)/4);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size, 0, _size*sqrt(3)/4);
            glRotatef(-90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, _size*sqrt(3)/4*3);
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _size);
        glPopMatrix();

        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

/* Srce se crta iz tri dela, trostrane prizme i dva poluvaljka */
void Heart::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);

        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, _height);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size/4, 0, -_size*sqrt(3)/4);
            glRotatef(180, 0, 1, 0);
            draw_cylinder(_height, _size/4, true);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-_size/4, 0, -_size*sqrt(3)/4);
            glRotatef(180, 0, 1, 0);
            draw_cylinder(_height, _size/4, true);
        glPopMatrix();

        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

/* Cvet se crta iz 6 valjaka koji predtavljaju latice */
void Flower::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);

        // Iscrtava se centralni valjak
        glPushMatrix();
            draw_cylinder(_size-0.1, _size*4/3, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size*4/3, 0, _size);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(_size*4/3, 0, -_size);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0, _size*4/3);
            draw_cylinder(_size-0.1, _size, false);
        glPopMatrix();

        //TODO: Popraviti cvet
//
//        glPushMatrix();
//            glTranslatef(_size/2, 0, _size);
//            draw_cylinder(_size-0.1, _size, false);
//        glPopMatrix();

        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

/* Trostrana prizma crta se od dva trougla medjusobno spojenih pravougaonicima */
void draw_prism(float size, float height)
{
    glBegin(GL_TRIANGLES);
        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0, size*sqrt(3)/4, -height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, -height/2);
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

bool operator==(const Color& left, const Color& right)
{
    float d1 = std::fabs(left.color_r - right.color_r);
    float d2 = std::fabs(left.color_g - right.color_g);
    float d3 = std::fabs(left.color_b - right.color_b);
    float eps = 0.01;

    return d1 <= eps && d2 <= eps && d3 <= eps;
}

bool operator<(const Color& left, const Color& right)
{
    if (left.color_r == right.color_r && left.color_g == right.color_g) {
        return left.color_b < right.color_b;
    } else if (left.color_r == right.color_r) {
        return left.color_g < right.color_g;
    } else {
        return left.color_r < right.color_r;
    }
}

