#include "shapes.hpp"

/* Iscrtava se kocka */
void Cube::draw(Color c)
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);

    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);
        glutSolidCube(_size);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

/* Iscrtava se odgovarajući kvadrat na glavnoj kocki */
void Cube::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);

    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
         * 2d iscrtavanje oblika na glavnoj kocki */
        switch(_id % 3)
        {
            /* Koriste se x i y osa za iscrtavnje */
            case 0:
                glBegin(GL_QUADS);
                    glVertex3f(-_size/2, _size/2, 0);
                    glVertex3f(-_size/2, -_size/2, 0);
                    glVertex3f(_size/2, -_size/2, 0);
                    glVertex3f(_size/2, _size/2, 0);
                glEnd();
                break;
                /* Koriste se y i z osa za iscrtavanje*/
            case 1:
                glBegin(GL_QUADS);
                    glVertex3f(0, _size/2, _size/2);
                    glVertex3f(0, -_size/2, _size/2);
                    glVertex3f(0, -_size/2, -_size/2);
                    glVertex3f(0, _size/2, -_size/2);
                glEnd();
                break;
                /* Koriste se x i z osa za iscrtavanje*/
            case 2:
                glBegin(GL_QUADS);
                    glVertex3f(-_size/2, 0, _size/2);
                    glVertex3f(_size/2, 0, _size/2);
                    glVertex3f(_size/2, 0, -_size/2);
                    glVertex3f(-_size/2, 0, -_size/2);
                glEnd();
                break;
            default:
                std::cout << "Entered default in switch; probably error..." << std::endl;
        }
    glPopMatrix();
}

