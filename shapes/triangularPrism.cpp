#include "shapes.hpp"

/* Iscrtava se trostrana prizma */
void TriangularPrism::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);
        draw_prism(_size, _height);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

/* Iscrtava se odgovarajući trougao na glavnoj kocki */
void TriangularPrism::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.x, xyz.y, xyz.z);

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

