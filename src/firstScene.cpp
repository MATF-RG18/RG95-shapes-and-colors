#include "firstScene.hpp"

std::shared_ptr<Shape> objects[NUM_OF_OBJECTS];
std::map<Color, int> object_colors;
std::map<Color, int> object_colors_on_cube;

float get_random_between_0_and_1();

void FirstScene::draw() const
{
    srand(time(nullptr));

    for (int i = 0; i < NUM_OF_OBJECTS; i++) {
        float size; // Uzima se slucajna velicia

        /* Parametrizuju se krugovi na kojima se nalaze objekti, kako bi se ravnomerno rasporedili */
        float t = (i % 10) * (2 * M_PI) / 10;
        float x = 0;
        float z = 0;

        /* Prvih 10 se raspoređuje na unutrašnji, manji krug, a narednih 10 na spoljašnji, veći krug */
        if(i < 10)
        {
            x =  MAIN_CUBE_SIZE * 4/3 * cos(t);
            z =  MAIN_CUBE_SIZE * 4/3 * sin(t);
        }
        else
        {
            x = MAIN_CUBE_SIZE * 2 * cos(t);
            z = MAIN_CUBE_SIZE * 2 * sin(t);
        }

        Coordinates xyz = {x, 0, z};

        /* Bira se nasumična vrsta i veličina objekta */
        int k = ((int)floor((get_random_between_0_and_1()) * 7) + i) % 7;
        switch (k) {
            case 0:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/4 - 0.8) + 0.5;
                objects[i] = std::make_shared<Sphere>(xyz, size);
                break;
            case 1:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/2 - 1) + 0.6;
                objects[i] = std::make_shared<Cube>(xyz, size);
                break;
            case 2:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/sqrt(3) - 0.7) + 0.7;
                objects[i] = std::make_shared<TriangularPrism>(xyz, (float)MAIN_CUBE_SIZE*sqrt(3)/4);
                break;
            case 3:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/4 - 0.8) + 0.5;
                objects[i] = std::make_shared<Cylinder>(xyz, size);
                break;
            case 4:
                size = get_random_between_0_and_1() * ((2 * (float)MAIN_CUBE_SIZE * (2 * sqrt(3) - 1) / 11) - 0.6) + 0.6;
                objects[i] = std::make_shared<Heart>(xyz, size);
                break;
            case 5:
                size = get_random_between_0_and_1() * 0.2 + 0.25;
                objects[i] = std::make_shared<Flower>(xyz, (float)MAIN_CUBE_SIZE/11);
                break;
            case 6:
                size = (get_random_between_0_and_1()) * ((float)MAIN_CUBE_SIZE / (4 * sqrt(3)) - 0.3) + 0.3;
                objects[i] = std::make_shared<Star>(xyz, size);
                break;
            default:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/4 - 0.5) + 0.5;
                objects[i] = std::make_shared<Sphere>(xyz, size);
        }

        object_colors.insert(std::pair<Color, int>(objects[i]->_c, i)); // Dodaje se boja objekata u niz

        /* Oduzimanje male vrednosti se vrsi kako bi sve sto je iscrtano na sceni imalo jedinstvenu boju,
         * što je potrebno za selekciju */
        float r = objects[i]->_c.color_r - 0.01;
        float g = objects[i]->_c.color_g - 0.01;
        float b = objects[i]->_c.color_b - 0.01;

        Color c = {r, g, b};

        object_colors_on_cube.insert(std::pair<Color, int>(c, i)); // Dodaje se boja na kocki u niz, što je potrebno zbog selekcije
        objects[i]->draw(); // Iscrtavaju se objekti
        objects[i]->draw_on_main_cube(c); // Iscrtavaju se odgovarajući objekti na kocki
    }
}

float get_random_between_0_and_1()
{
    return (float) rand() / (RAND_MAX);
}
