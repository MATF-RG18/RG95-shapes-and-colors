#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__ 1

#include <ostream>
#include <GL/glut.h>
#include <GL/glu.h>

struct Color {
    float color_r;
    float color_g;
    float color_b;
};

bool operator==(const Color& left, const Color& right);
bool operator<(const Color& left, const Color& right);

struct Coordinates {
    float center_x;
    float center_y;
    float center_z;
};

#define NUM_OF_OBJECTS 10
#define MAX_COLORS 10

/* Nizovi komponenti boja */
const float r_values[MAX_COLORS] = {1, 0, 0, 1, 1, 0, 0.6, 0, 0.6, 0};
const float g_values[MAX_COLORS] = {0, 0, 1, 0, 0.5, 1, 0, 0.6, 0.25, 0};
const float b_values[MAX_COLORS] = {0, 1, 0, 0.6, 0, 1, 0.4, 0.3, 1, 0.6};

void draw_prism(float size, float height);
void draw_cylinder(float height, float base, bool half);

class Shape {
public:
    Shape(Coordinates xyz, float size)
        : _xyz(xyz), _size(size)
    {
        /*  Boja koja se dobija jedinstveno iz niza boja na osnovu vrednosti promenljive id */
        _c.color_r = r_values[id%NUM_OF_OBJECTS];
        _c.color_g = g_values[id%NUM_OF_OBJECTS];
        _c.color_b = b_values[id%NUM_OF_OBJECTS];

        id++;

        /* Inicijalizuje se sistem objekta na jedinicnu matricu */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    }

    Color _c;
    virtual void draw() = 0;
    virtual ~Shape() {
    }

protected:
    Coordinates _xyz;
    float _size;
    float _system[16];

private:
    static unsigned int id;
};

class Sphere : public Shape {
public:
    Sphere(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw();
};

class Cube : public Shape {
public:
    Cube(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw();
};

class TriangularPrism: public Shape {
public:
    TriangularPrism(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size;
    }

    void draw();
private:
    float _height;
};

class Cylinder : public Shape {
public:
    Cylinder(Coordinates xyz, float base)
    : Shape(xyz, base)
    {
        _height = base * 2;
    }

    void draw();
private:
    float _height;
};

class Star : public Shape {
public:
    Star(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw();
};

class Flower : public Shape {
public:
    Flower(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw();
};

class Heart : public Shape {
public:
    Heart(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size / 2;
    }

    void draw();
private:
    float _height;
};

#endif