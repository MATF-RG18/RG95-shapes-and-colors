#include "mainCube.hpp"

void MainCube::draw() const
{
    glColor3f(0.62, 0.32, 0.18);
    glPushMatrix();
        glutSolidCube(_size);
    glPopMatrix();
}

float MainCube::getSize() const
{
    return _size;
}