#ifndef __FIRST_SCENE_HPP
#define __FIRST_SCENE_HPP 1

/* Kada se prvi put iscrtava scena, inicijalizuje se niz objekata na slučajan nacin, kao i njihove boje.
 * Takođe, inicijalizuje se mapa koja sadrži informacije da li su upareni objekat i odgovarajući oblik na kocki,
 * ili ne */

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

    void initialize_objects() const;
private:
    FirstScene() = default;
};

#endif