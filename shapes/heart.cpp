#include "shapes.hpp"

/* Srce se crta iz tri dela, trostrane prizme i dva poluvaljka */
void Heart::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.x, _xyz.y, _xyz.z);

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

        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            draw_prism(_size, cylinder_height);
        glPopMatrix();

        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

/* Iscrtava se odgovarajuće srce na glavnoj kocki */
void Heart::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.x, xyz.y, xyz.z);

        /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
             * 2d iscrtavanje oblika na glavnoj kocki */
        switch(_id%3)
        {
            /* Koriste se x i y osa za iscrtavnje */
            case 0:
                glBegin(GL_TRIANGLES);
                    glVertex3f(0, -_size*sqrt(3)/3, 0);
                    glVertex3f(_size/2, _size*sqrt(3)/6, 0);
                    glVertex3f(-_size/2, _size*sqrt(3)/6, 0);
                glEnd();

                glPushMatrix();
                    glTranslatef(_size/4, _size*sqrt(3)/6, 0);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(_size/4, 0, 0);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(cos(i)*_size/4, -sin(i)*_size/4, 0);
                                continue;
                            }

                            glVertex3f(cos(i)*_size/4, sin(i)*_size/4, 0);
                        }
                        glVertex3f(-_size/4, 0, 0);
                    glEnd();
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(-_size/4, _size*sqrt(3)/6, 0);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(_size/4, 0, 0);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(cos(i)*_size/4, -sin(i)*_size/4, 0);
                                continue;
                            }

                            glVertex3f(cos(i)*_size/4, sin(i)*_size/4, 0);
                        }
                        glVertex3f(-_size/4, 0, 0);
                    glEnd();
                glPopMatrix();
                break;
                /* Koriste se y i z osa za iscrtavanje*/
            case 1:
                glBegin(GL_TRIANGLES);
                    glVertex3f(0, -_size*sqrt(3)/3, 0);
                    glVertex3f(0, _size*sqrt(3)/6, -_size/2);
                    glVertex3f(0, _size*sqrt(3)/6, _size/2);
                glEnd();

                glPushMatrix();
                    glTranslatef(0, _size*sqrt(3)/6, -_size/4);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, 0, -_size/4);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(0, -sin(i)*_size/4, cos(i)*_size/4);
                                continue;
                            }

                            glVertex3f(0, sin(i)*_size/4, cos(i)*_size/4);
                        }
                        glVertex3f(0, 0, _size/4);
                    glEnd();
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0, _size*sqrt(3)/6, _size/4);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, 0, -_size/4);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(0, -sin(i)*_size/4, cos(i)*_size/4);
                                continue;
                            }

                            glVertex3f(0, sin(i)*_size/4, cos(i)*_size/4);
                        }
                        glVertex3f(0, 0, _size/4);
                    glEnd();
                glPopMatrix();
                break;
                /* Koriste se x i z osa za iscrtavanje*/
            case 2:
                glBegin(GL_TRIANGLES);
                    glVertex3f(0, 0, _size*sqrt(3)/3);
                    glVertex3f(_size/2, 0, -_size*sqrt(3)/6);
                    glVertex3f(-_size/2, 0, -_size*sqrt(3)/6);
                glEnd();

                glPushMatrix();
                    glTranslatef(_size/4, 0, -_size*sqrt(3)/6);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(_size/4, 0, 0);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(cos(i)*_size/4, 0, sin(i)*_size/4);
                                continue;
                            }

                            glVertex3f(cos(i)*_size/4, 0, -sin(i)*_size/4);
                        }
                        glVertex3f(-_size/4, 0, 0);
                    glEnd();
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(-_size/4, 0, -_size*sqrt(3)/6);
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex3f(0, 0, 0);
                        glVertex3f(_size/4, 0, 0);
                        for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                        {
                            if(sin(i) < 0)
                            {
                                glVertex3f(cos(i)*_size/4, 0, sin(i)*_size/4);
                                continue;
                            }

                            glVertex3f(cos(i)*_size/4, 0, -sin(i)*_size/4);
                        }
                        glVertex3f(-_size/4, 0, 0);
                    glEnd();
                glPopMatrix();

                break;
            default:
                std::cout << "Entered default in switch; probably error..." << std::endl;
        }
    glPopMatrix();
}