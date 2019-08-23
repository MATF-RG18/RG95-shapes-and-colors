#include "shapes.hpp"

/* Iscrtava se cilindar */
void Cylinder::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);
        draw_cylinder(_height, _size, false);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

/* Iscrtava se odgovarajući krug na glavnoj kocki */
void Cylinder::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.x, xyz.y, xyz.z);

        glBegin(GL_TRIANGLE_FAN);
        /* Postoje tri grupe strana na osnovu toga koje ose se koriste
         * za 2d iscrtavanje oblika na glavnoj kocki*/
            switch(_id%3)
            {
                /* Koriste se x i y osa za iscrtavnje */
                case 0:
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size, sin(i)*_size, 0);
                    }
                    break;
                    /* Koriste se y i z osa za iscrtavanje*/
                case 1:
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(0, cos(i)*_size, sin(i)*_size);
                    }
                    break;
                    /* Koriste se x i z osa za iscrtavanje*/
                case 2:
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size, 0, sin(i)*_size);
                    }
                    break;
                default:
                    std::cout << "Entered default in switch; probably error..." << std::endl;
            }
        glEnd();
    glPopMatrix();
}