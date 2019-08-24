#include "shapes.hpp"

/* Iscrtava se trostrana prizma */
void TriangularPrism::draw(Color c)
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);
    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);
        draw_prism(_size, _height);
    glPopMatrix();
}

/* Iscrtava se odgovarajući trougao na glavnoj kocki */
void TriangularPrism::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);

    glPushMatrix();
        glBegin(GL_TRIANGLES);
            /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
                 * 2d iscrtavanje oblika na glavnoj kocki */
            switch(_id%3)
            {
                /* Koriste se x i y osa za iscrtavnje */
                case 0:
                    glVertex3f(0, _size*sqrt(3)/3, 0);
                    glVertex3f(-_size/2, -_size*sqrt(3)/6, 0);
                    glVertex3f(_size/2, -_size*sqrt(3)/6, 0);
                    break;
                    /* Koriste se y i z osa za iscrtavanje*/
                case 1:
                    glVertex3f(0, _size*sqrt(3)/3, 0);
                    glVertex3f(0, -_size*sqrt(3)/6, _size/2);
                    glVertex3f(0, -_size*sqrt(3)/6, -_size/2);
                    break;
                    /* Koriste se x i z osa za iscrtavanje*/
                case 2:
                    glVertex3f(0, 0, -_size*sqrt(3)/3);
                    glVertex3f(-_size/2, 0, _size*sqrt(3)/6);
                    glVertex3f(_size/2, 0, _size*sqrt(3)/6);
                    break;
                default:
                    std::cout << "Entered default in switch; probably error..." << std::endl;
            }
        glEnd();
    glPopMatrix();
}

