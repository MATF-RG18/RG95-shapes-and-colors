#include "mainCube.hpp"

void MainCube::draw() const
{
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        /* Prednja strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        /* Bocna desna strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        /* Zadnja strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        /* Bocna leva strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        /* Gornja strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        /* Donja strana kocke */
        glTexCoord2f(0, 1);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(0, 0);
        glVertex3f(-(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 0);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2);

        glTexCoord2f(1, 1);
        glVertex3f((float)MAIN_CUBE_SIZE/2, -(float)MAIN_CUBE_SIZE/2, (float)MAIN_CUBE_SIZE/2);
    glEnd();
}