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

struct Coordinates {
    float x;
    float y;
    float z;
};

bool operator==(const Coordinates& left, const Coordinates& right);
bool operator<(const Coordinates& left, const Coordinates& right);

/* Nizovi komponenti boja */
const float r_values[MAX_COLORS] = {255, 0, 0, 240, 210, 128, 255, 0, 128, 245, 70, 230, 0, 250, 170, 60, 145, 255, 204, 80};
const float g_values[MAX_COLORS] = {0, 255, 0, 50, 245, 0, 225, 0, 128, 130, 240, 25, 130, 190, 110, 180, 30, 140, 78, 200};
const float b_values[MAX_COLORS] = {0, 0, 255, 230, 60, 0, 25, 128, 128, 48, 240, 75, 200, 190, 40, 75, 180, 0, 92, 120};

Coordinates cross_product(Coordinates a, Coordinates b); // Pomoćna funkcija za računanje vektorskog proizvoda
Coordinates calculate_normal(Coordinates a, Coordinates b, Coordinates c); // Pomoćna funkcija za računanje normale
void draw_prism(float size, float height); // Pomoćna funkcija za crtanje trostrane prizme
void draw_cylinder(float height, float base); // Pomoćna funkcija za crtanje valjka

extern std::map<int, Coordinates> places_on_main_cube; // Mapira se id u poziciju oblika na glavnoj kocki

class Shape {
public:
    Shape(Coordinates xyz, float size)
    : _xyz(xyz), _size(size)
    {
        _id = next_available_id;
        next_available_id++;

        /*  Boja koja se dobija jedinstveno iz niza boja na osnovu vrednosti promenljive id */
        _c.color_r = r_values[_id%NUM_OF_OBJECTS];
        _c.color_g = g_values[_id%NUM_OF_OBJECTS];
        _c.color_b = b_values[_id%NUM_OF_OBJECTS];
    }

    Coordinates _xyz; // Pozicija objekta na zamišljenom krugu
    int getId() const;
    const Color &getC() const;
    virtual void draw(Color c) = 0; // Metod koji iscrtava objekat
    virtual void draw_on_main_cube(Color c) const = 0; // Metod koji iscrtava odgovarajući oblik na kocki
    virtual ~Shape() = default;
protected:
    int _id; // identifikator objekta
    float _size; // Veličina objekta
    Color _c; // Boja kojom se boji element
    static unsigned int next_available_id; // Brojač napravljenih objekata
};

class Sphere : public Shape {
public:
    Sphere(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
};

class Cube : public Shape {
public:
    Cube(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
};

class TriangularPrism: public Shape {
public:
    TriangularPrism(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size;
    }

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
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

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
private:
    float _height;
};

class Star : public Shape {
public:
    Star(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
};

class Flower : public Shape {
public:
    Flower(Coordinates xyz, float size)
    : Shape(xyz, size)
    {}

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
};

class Heart : public Shape {
public:
    Heart(Coordinates xyz, float size)
    : Shape(xyz, size)
    {
        _height = size / 2;
    }

    void draw(Color c) override;
    void draw_on_main_cube(Color c) const override;
private:
    float _height;
};

#endif