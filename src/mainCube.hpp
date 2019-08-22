#ifndef __MAIN_CUBE_HPP__
#define __MAIN_CUBE_HPP__ 1

/**
 * Implementacija osnovne drvene kutije u koju se ubacuju oblici.
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define MAIN_CUBE_SIZE 3

class MainCube {
public:
    MainCube(float size = MAIN_CUBE_SIZE)
    : _size(size)
    {}

    void draw() const;
    float getSize() const;
private:
    float _size;
};

#endif