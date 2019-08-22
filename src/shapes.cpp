#include "shapes.hpp"
#include "mainCube.hpp"
#include <cmath>
#include <iostream>

#define NUM_OF_VERTEXES 200

unsigned int Shape::next_available_id = 0;
std::map<int, Coordinates> places_on_main_cube; // Mapira se id u poziciju na glavnoj kocki

void Sphere::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        glutSolidSphere(_size, 30, 30);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system); // Pamti se sistem objekta
    glPopMatrix();
}

void Sphere::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

        glBegin(GL_TRIANGLE_FAN);
        /* Postoje tri grupe strana na osnovu toga koje ose se koriste
         * za 2d iscrtavanje oblika na glavnoj kocki*/
        switch(_id % 3)
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

void Cube::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        glutSolidCube(_size);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void Cube::draw_on_main_cube(Color c) const
{
        glColor3f(c.color_r, c.color_g, c.color_b);

        glPushMatrix();
            Coordinates xyz = places_on_main_cube.find(_id)->second;
            glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
                 * 2d iscrtavanje oblika na glavnoj kocki */
                switch(_id%3)
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

void TriangularPrism::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        draw_prism(_size, _height);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void TriangularPrism::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

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

void Cylinder::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);
        draw_cylinder(_height, _size, false);
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void Cylinder::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

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

void Star::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

        glBegin(GL_TRIANGLES);
            /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
                 * 2d iscrtavanje oblika na glavnoj kocki */
            switch(_id%3)
            {
                /* Koriste se x i y osa za iscrtavnje */
                case 0:
                    glVertex3f(-3*_size/2, _size*sqrt(3)/2, 0);
                    glVertex3f(0, -_size*sqrt(3), 0);
                    glVertex3f(3*_size/2, _size*sqrt(3)/2, 0);

                    glVertex3f(0, _size*sqrt(3), 0);
                    glVertex3f(-3*_size/2, -_size*sqrt(3)/2, 0);
                    glVertex3f(3*_size/2, -_size*sqrt(3)/2, 0);
                    break;
                    /* Koriste se y i z osa za iscrtavanje*/
                case 1:
                    glVertex3f(0, _size*sqrt(3)/2, 3*_size/2);
                    glVertex3f(0, -_size*sqrt(3), 0);
                    glVertex3f(0, _size*sqrt(3)/2, -3*_size/2);

                    glVertex3f(0, _size*sqrt(3), 0);
                    glVertex3f(0, -_size*sqrt(3)/2, 3*_size/2);
                    glVertex3f(0, -_size*sqrt(3)/2, -3*_size/2);
                    break;
                    /* Koriste se x i z osa za iscrtavanje*/
                case 2:
                    glVertex3f(-3*_size/2, 0, -_size*sqrt(3)/2);
                    glVertex3f(0, 0, _size*sqrt(3));
                    glVertex3f(3*_size/2, 0, -_size*sqrt(3)/2);

                    glVertex3f(0, 0, -_size*sqrt(3));
                    glVertex3f(-3*_size/2, 0, _size*sqrt(3)/2);
                    glVertex3f(3*_size/2, 0, _size*sqrt(3)/2);
                    break;
                default:
                    std::cout << "Entered default in switch; probably error..." << std::endl;
            }
        glEnd();
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

void Heart::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

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

/* Cvet se crta iz 6 valjaka koji predtavljaju latice */
void Flower::draw()
{
    glColor3f(_c.color_r, _c.color_g, _c.color_b);

    glPushMatrix();
        glTranslatef(_xyz.center_x, _xyz.center_y, _xyz.center_z);

        // Iscrtava se centralni valjak
        glPushMatrix();
            draw_cylinder(_size, _size*4/3, false);
        glPopMatrix();

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

        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    glPopMatrix();
}

void Flower::draw_on_main_cube(Color c) const
{
    glColor3f(c.color_r, c.color_g, c.color_b);

    glPushMatrix();
        Coordinates xyz = places_on_main_cube.find(_id)->second;
        glTranslatef(xyz.center_x, xyz.center_y, xyz.center_z);

        /* Postoje tri grupe strana na osnovu toga koje ose se koriste za
             * 2d iscrtavanje oblika na glavnoj kocki */
        switch(_id%3)
        {
            /* Koriste se x i y osa za iscrtavnje */
            case 0:
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size * 4/3, sin(i)*_size * 4/3, 0);
                    }
                glEnd();

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
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(0, sin(i)*_size * 4/3, cos(i)*_size * 4/3);
                    }
                glEnd();

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
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0, 0, 0);
                    for(int i = 0; i <= NUM_OF_VERTEXES; i++)
                    {
                        glVertex3f(cos(i)*_size * 4/3, 0, sin(i)*_size * 4/3);
                    }
                glEnd();

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
        for(j = 0; j <= NUM_OF_VERTEXES; j++)
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
    float eps = 0.05;

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

bool operator==(const Coordinates& left, const Coordinates& right)
{
    float d1 = std::fabs(left.center_x- right.center_x);
    float d2 = std::fabs(left.center_y - right.center_y);
    float d3 = std::fabs(left.center_z - right.center_z);
    float eps = 0.001;

    return d1 <= eps && d2 <= eps && d3 <= eps;
}

bool operator<(const Coordinates& left, const Coordinates& right)
{
    if (left.center_x == right.center_x && left.center_y == right.center_y) {
        return left.center_z < right.center_z;
    } else if (left.center_x == right.center_x) {
        return left.center_y < right.center_y;
    } else {
        return left.center_x < right.center_x;
    }
}

void get_coordinates()
{
    Coordinates xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(0, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(1, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(2, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(3, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(4, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(5, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(6, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(7, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(8, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(9, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(10, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(11, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(12, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(13, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(14, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(15, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(16, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(17, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(18, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(19, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(20, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(21, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(22, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(23, xyz));
}
