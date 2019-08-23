#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__ 1

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <map>
#include <cmath>
#include "../src/mainCube.hpp"

#define NUM_OF_OBJECTS 20
#define MAX_COLORS 20
#define NUM_OF_VERTEXES 300
#define EPS 0.05

struct Color {
    float color_r;
    float color_g;
    float color_b;
};

bool operator==(const Color& left, const Color& right);
bool operator<(const Color& left, const Color& right);

struct Coordinates {
    float x;
    float y;
    float z;
};

bool operator==(const Coordinates& left, const Coordinates& right);
bool operator<(const Coordinates& left, const Coordinates& right);

/* Nizovi komponenti boja */
const float r_values[MAX_COLORS] = {1, 0, 0, 0, 1, 1, 0, 0, 1, 0.7, 0.4, 1, 0.4, 0.7, 1, 0.5, 0.5, 1, 0.3, 1};
const float g_values[MAX_COLORS] = {0, 0, 1, 1, 1, 0, 1, 0.4, 0.5, 0.4, 0.7, 0.6, 0.2, 0.7, 0, 1, 0.5, 0.8, 0, 0.7};
const float b_values[MAX_COLORS] = {0, 1, 0, 0.5, 0, 0.5, 1, 0, 0, 1, 1, 1, 0, 0.7, 1, 0.8, 0.5, 0, 0.5, 0.8};

Coordinates cross_product(Coordinates a, Coordinates b);
Coordinates calculate_normal(Coordinates x, Coordinates y);
void draw_prism(float size, float height);
void draw_cylinder(float height, float base, bool half);

extern std::map<int, Coordinates> places_on_main_cube; // Mapira se id u poziciju oblika na glavnoj kocki
extern float cylinder_height;

class Shape {
public:
    Shape(Coordinates xyz, float size)
        : _xyz(xyz), _size(size)
    {
        _id = next_available_id;

        /*  Boja koja se dobija jedinstveno iz niza boja na osnovu vrednosti promenljive id */
        _c.color_r = r_values[_id%NUM_OF_OBJECTS];
        _c.color_g = g_values[_id%NUM_OF_OBJECTS];
        _c.color_b = b_values[_id%NUM_OF_OBJECTS];

        next_available_id++;

        /* Inicijalizuje se sistem objekta na jedinicnu matricu */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glGetFloatv(GL_MODELVIEW_MATRIX, _system);
    }

    Color _c;
    float _system[16];
    virtual void draw() = 0;
    virtual void draw_on_main_cube(Color c) const = 0;
    virtual ~Shape() = default;

protected:
    Coordinates _xyz;
    int _id;
    float _size;
    static unsigned int next_available_id;
};

class Sphere : public Shape {
public:
    Sphere(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw() override;
    void draw_on_main_cube(Color c) const override;
};

class Cube : public Shape {
public:
    Cube(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw() override;
    void draw_on_main_cube(Color c) const override;
};

class TriangularPrism: public Shape {
public:
    TriangularPrism(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size;
    }

    void draw() override;
    void draw_on_main_cube(Color c) const;
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

    void draw() override;
    void draw_on_main_cube(Color c) const;
private:
    float _height;
};

class Star : public Shape {
public:
    Star(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw() override;
    void draw_on_main_cube(Color c) const;
};

class Flower : public Shape {
public:
    Flower(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw() override;
    void draw_on_main_cube(Color c) const;
};

class Heart : public Shape {
public:
    Heart(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size / 2;
    }

    void draw() override;
    void draw_on_main_cube(Color c) const;
private:
    float _height;
};

#endif