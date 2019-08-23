#include "shapes.hpp"

/* Cvet se crta iz 6 valjaka: centralnog valjka i 5 njih koji predstavljaju latice
 * i ravnomerno su raspoređeni na zamišljenom krugu oko centralnog valjka */
void Flower::draw(Color c)
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);

    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);

        // Iscrtava se centralni valjak
        glPushMatrix();
            draw_cylinder(_size, _size*4/3, false);
        glPopMatrix();

        /* Parametrizuje se zamišljeni krug na kom se nalaze centri 5 valjaka koji predstavljaju latice,
         * kako bi bili ravnomerno raspoređeni */
        for(int i = 0; i < 5; i++)
        {
            double t = i * (2 * M_PI) / 5;
            float x = _size * 3 / 2 * cos(t);
            float z = _size * 3 / 2 * sin(t);

            glPushMatrix();
                glTranslatef(x, 0, z);
                draw_cylinder(_size, _size, false);
            glPopMatrix();
        }

        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

/* Iscrtava se odgovarajući cvet na glavnoj kocki */
void Flower::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r/255.0, c.color_g/255.0, c.color_b/255.0);

    glPushMatrix();
        /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
             * 2d iscrtavanje oblika na glavnoj kocki */
        switch(_id % 3)
        {
            /* Koriste se x i y osa za iscrtavnje */
            case 0:
                // Iscrtava se centralni krug
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size * 4/3, sin(i)*_size * 4/3, 0);
                    }
                glEnd();

                /* Ponovo se parametrizuje se zamišljeni krug na kom se nalaze centri 5 valjaka koji
                 * predstavljaju latice, kako bi bili ravnomerno raspoređeni */
                for(int i = 0; i < 5; i++)
                {
                    double t = i * (2 * M_PI) / 5;
                    float x = _size * 3 / 2 * cos(t);
                    float y = _size * 3 / 2 * sin(t);

                    glPushMatrix();
                        glTranslatef(x, y, 0);
                        glBegin(GL_TRIANGLE_FAN);
                            glVertex3f(0, 0, 0);
                            for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                            {
                                glVertex3f(cos(i)*_size, sin(i)*_size, 0);
                            }
                        glEnd();
                    glPopMatrix();
                }
                break;
                /* Koriste se y i z osa za iscrtavanje*/
            case 1:
                // Iscrtava se centralni krug
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(0, sin(i)*_size * 4/3, cos(i)*_size * 4/3);
                    }
                glEnd();

                /* Ponovo se parametrizuje se zamišljeni krug na kom se nalaze centri 5 valjaka koji
                 * predstavljaju latice, kako bi bili ravnomerno raspoređeni */
                for(int i = 0; i < 5; i++)
                {
                    double t = i * (2 * M_PI) / 5;
                    float z = _size * 3 / 2 * cos(t);
                    float y = _size * 3 / 2 * sin(t);

                    glPushMatrix();
                        glTranslatef(0, y, z);
                        glBegin(GL_TRIANGLE_FAN);
                            glVertex3f(0, 0, 0);
                            for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                            {
                                glVertex3f(0, sin(i)*_size, cos(i)*_size);
                            }
                        glEnd();
                    glPopMatrix();
                }
                break;
                /* Koriste se x i z osa za iscrtavanje*/
            case 2:
                // Iscrtava se centralni krug
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size * 4/3, 0, sin(i)*_size * 4/3);
                    }
                glEnd();

                /* Ponovo se parametrizuje se zamišljeni krug na kom se nalaze centri 5 valjaka koji
                 * predstavljaju latice, kako bi bili ravnomerno raspoređeni */
                for(int i = 0; i < 5; i++)
                {
                    double t = i * (2 * M_PI) / 5;
                    float x = _size * 3 / 2 * cos(t);
                    float z = _size * 3 / 2 * sin(t);

                    glPushMatrix();
                        glTranslatef(x, 0, z);
                        glBegin(GL_TRIANGLE_FAN);
                            glVertex3f(0, 0, 0);
                            for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                            {
                                glVertex3f(cos(i)*_size, 0, sin(i)*_size);
                            }
                        glEnd();
                    glPopMatrix();
                }
                break;
            default:
                std::cout << "Entered default in switch; probably error..." << std::endl;
        }
    glPopMatrix();
}