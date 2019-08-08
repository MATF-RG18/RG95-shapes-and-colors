#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__ 1

void draw_prism(float size);
void draw_cylinder(float height, float base, bool half);
void draw_base(float height, float base, bool half);

class Shape{
public:
    Shape(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : _center_x(center_x), _center_y(center_y), _center_z(center_z), _color_r(color_r), _color_b(color_b), _color_g(color_g), _size(size)
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
    float _size;
};

class Sphere : public Shape {
public:
    Sphere(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};

class Cube : public Shape {
public:
    Cube(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};

class TriangularPrism: public Shape {
public:
    TriangularPrism(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};

class Cylinder : public Shape {
public:
    Cylinder(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float height, float base)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, base), _height(height)
    {}

    void draw() const;
private:
    float _height;
};

class Star : public Shape {
public:
    Star(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};

class Flower : public Shape {
public:
    Flower(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};

class Heart : public Shape {
public:
    Heart(float color_r, float color_g, float color_b, float center_x, float center_y, float center_z, float size)
    : Shape(color_r, color_g, color_b, center_x, center_y, center_z, size)
    {}

    void draw() const;
};


#endif