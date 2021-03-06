#include "firstScene.hpp"

std::shared_ptr<Shape> objects[NUM_OF_OBJECTS]; // Niz objekata
std::map<int, Coordinates> places_on_main_cube; // Mapa koja preslikava identifikator u mesto na glavnoj kocki
std::map<int, bool> matched_objects; // Mapa koja preslikava identifikator u informaciju da li su objekti upareni

float get_random_between_0_and_1(); // Pomoćna funkcija koja vraća slučajan broj između 0 i 1
void get_places_on_main_cube(); // Pomoćna funkcija koja inicijalizuje mapu za mesta na kocki

void FirstScene::initialize_objects() const
{
    get_places_on_main_cube(); // Inicijalizuju se koordinate na kocki
    srand(time(nullptr));

    for (int i = 0; i < NUM_OF_OBJECTS; i++)
    {
        matched_objects.insert(std::pair<int, bool>(i, false)); // Inicijalizuje se mapa uparenih oblika

        float size; // Uzima se slučajna veličina

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
        switch (k)
        {
            case 0:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/4 - 0.8) + 0.5;
                objects[i] = std::make_shared<Sphere>(xyz, size);
                break;
            case 1:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/2 - 1) + 0.6;
                objects[i] = std::make_shared<Cube>(xyz, size);
                break;
            case 2:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/sqrt(3) - 0.8) + 0.7;
                objects[i] = std::make_shared<TriangularPrism>(xyz, (float)MAIN_CUBE_SIZE*sqrt(3)/4);
                break;
            case 3:
                size = get_random_between_0_and_1() * ((float)MAIN_CUBE_SIZE/4 - 0.8) + 0.5;
                objects[i] = std::make_shared<Cylinder>(xyz, size);
                break;
            case 4:
                size = get_random_between_0_and_1() * ((2 * (float)MAIN_CUBE_SIZE * (2 * sqrt(3) - 1) / 11) - 0.7) + 0.6;
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
    }
}

float get_random_between_0_and_1()
{
    return (float) rand() / (RAND_MAX);
}

void get_places_on_main_cube()
{
    Coordinates xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(0, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(1, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(2, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(3, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(4, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(5, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(6, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(7, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(8, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(9, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(10, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(11, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(12, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(13, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(14, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(15, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(16, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(17, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(18, xyz));
    xyz = {(float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(19, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/2 + 0.01, (float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(20, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, (float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01};
    places_on_main_cube.insert(std::pair<int, Coordinates>(21, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(22, xyz));
    xyz = {-(float)MAIN_CUBE_SIZE/4, -(float)MAIN_CUBE_SIZE/2 - 0.01, -(float)MAIN_CUBE_SIZE/4};
    places_on_main_cube.insert(std::pair<int, Coordinates>(23, xyz));
}
