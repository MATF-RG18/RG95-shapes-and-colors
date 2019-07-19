#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__ 1

#include <iostream>

class Shape{
public:
    Shape(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z)
    : _center_x(center_x), _center_y(center_y), _center_z(center_z), _color_r(color_r), _color_b(color_b), _color_g(color_g)
    {}

    virtual void draw() const = 0;
    virtual ~Shape() {
    }

protected:
    float _color_r;
    float _color_g;
    float _color_b;
    float _center_x;
    float _center_y;
    float _center_z;
};

class Sphere : public Shape {
public:
    Sphere(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float radius)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z), _radius(radius)
    {}

    void draw() const;
private:
    float _radius;
};

class Cube : public Shape {
public:
    Cube(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z), _size(size)
    {}

    void draw() const;
private:
    float _size;
};

class TriangularPrism: public Shape {
public:
    TriangularPrism(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z), _size(size)
    {}

    void draw() const;
private:
    float _size;
};

class Cylinder : public Shape {

};

class Star : public Shape {

};

class Flower : public Shape {

};

class Heart : public Shape {

};

class Moon : public Shape {

};

class Diamond : public Shape {

};

#endif