/* Fajl sa pomoćnim funkcijama */

#include "shapes.hpp"

unsigned int Shape::next_available_id = 0;
float cylinder_height = 0;

int Shape::getId() const {
    return _id;
}

const Color &Shape::getC() const {
    return _c;
}

Coordinates cross_product(Coordinates a, Coordinates b)
{
    Coordinates c = {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z,
                     a.x*b.y - a.y*b.x};

    return c;
}

Coordinates calculate_normal(Coordinates a, Coordinates b, Coordinates c)
{
    Coordinates ba = {b.x - a.x, b.y - a.y, b.z - a.z};
    Coordinates ca = {c.x - a.x, c.y - a.y, b.z - a.z};

    return cross_product(ba, ca);
}

/* Trostrana prizma crta se od dva trougla medjusobno spojenih pravougaonicima */
void draw_prism(float size, float height)
{
    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);

        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        Coordinates a = {size/2, -size*(float)sqrt(3)/4, -height/2};
        Coordinates b = {0, size*(float)sqrt(3)/4, -height/2};
        Coordinates c = {0, size*(float)sqrt(3)/4, height/2};
        Coordinates result = calculate_normal(c, b, a);
        glNormal3f(result.x, result.y, result.z);

        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        a = {0, size*(float)sqrt(3)/4, -height/2};
        b = {-size/2, -size*(float)sqrt(3)/4, -height/2};
        c = {-size/2, -size*(float)sqrt(3)/4, height/2};
        result = calculate_normal(a, b, c);
        glNormal3f(result.x, result.y, result.z);

        glVertex3f(0, size*sqrt(3)/4, -height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(0, size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_QUADS);
        a = {-size/2, -size*(float)sqrt(3)/4, -height/2};
        b = {size/2, -size*(float)sqrt(3)/4, -height/2};
        c = {size/2, -size*(float)sqrt(3)/4, height/2};
        result = calculate_normal(a, b, c);
        glNormal3f(result.x, result.y, result.z);

        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, height/2);
        glVertex3f(-size/2, -size*sqrt(3)/4, height/2);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, -1);
        glVertex3f(-size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(size/2, -size*sqrt(3)/4, -height/2);
        glVertex3f(0, size*sqrt(3)/4, -height/2);
    glEnd();
}

/* half parametar oznacava da li se iscrtava ceo ili polovina cilindra*/
void draw_cylinder(float height, float base, bool half)
{
    double i,j;
    int h = 2;

    if(half)
       h = 1;

    glPushMatrix();
        glTranslatef(0, -(height/2), 0);

        /* Iscrtava se omot cilindra */
        for(i = 0; i < height; i += height / 20)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for(j = 0; j <= M_PI*h + 0.01; j += M_PI / 20)
            {
                glNormal3f(cos(j)*base, 0, sin(j)*base);
                glVertex3f(cos(j)*base, i, sin(j)*base);

                glNormal3f(cos(j)*base, 0, sin(j)*base);
                cylinder_height = i+height/20;
                glVertex3f(cos(j)*base, cylinder_height, sin(j)*base);
            }

            glEnd();
        }

        /* Iscrtavaju se baze cilindra */
        for(i = 0; i <= cylinder_height; i += cylinder_height)
        {
            glBegin(GL_TRIANGLE_FAN);
                if(i == 0)
                    glNormal3f(0, -1, 0);
                else
                    glNormal3f(0, 1, 0);

                glVertex3f(0, i, 0);
                for(j = 0; j <= NUM_OF_VERTEXES; j++)
                {
                    if(sin(j) < 0 && half)
                    {
                        glVertex3f(cos(j)*base, i , -sin(j)*base);
                    }

                    glVertex3f(cos(j)*base, i, sin(j)*base);
                }
            glEnd();
        }
    glPopMatrix();
}

bool operator==(const Coordinates& left, const Coordinates& right)
{
    float d1 = std::fabs(left.x- right.x);
    float d2 = std::fabs(left.y - right.y);
    float d3 = std::fabs(left.z - right.z);

    return d1 <= EPS && d2 <= EPS && d3 <= EPS;
}

bool operator<(const Coordinates& left, const Coordinates& right)
{
    if (left.x == right.x && left.y == right.y)
    {
        return left.z < right.z;
    }
    else if (left.x == right.x)
    {
        return left.y < right.y;
    }
    else
    {
        return left.x < right.x;
    }
}

