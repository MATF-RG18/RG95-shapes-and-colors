#ifndef __FIRST_SCENE_HPP
#define __FIRST_SCENE_HPP 1

/* Kada se prvi put iscrtava scena, inicijalizuje se niz objekata na slucajan nacin, kao i njihove boje */

#include <cmath>
#include <memory>
#include "mainCube.hpp"
#include "../shapes/shapes.hpp"

class FirstScene {
public:
    static FirstScene& getInstance()
    {
        static FirstScene instance;

        return instance;
    }

    void draw() const;
private:
    FirstScene() = default;
};

#endif