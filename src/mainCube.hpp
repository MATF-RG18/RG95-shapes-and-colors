#ifndef __MAIN_CUBE_HPP__
#define __MAIN_CUBE_HPP__ 1

/**
 * Implementacija osnovne drvene kutije u koju se ubacuju oblici.
 */

#define SIZE 3

class MainCube {
public:
    MainCube(float size = SIZE)
    : _size(size)
    {}

    void draw() const;
    float getSize() const;
private:
    float _size;
};

#endif