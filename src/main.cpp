#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <random>
#include <map>
#include "mainCube.hpp"
#include "shapes.hpp"

int window_w, window_h; // Pri promeni pamti se širina i visina prozora
int mouse_x = 0, mouse_y = 0; // Pri promeni pamti se pozicija miša
float rotation_matrix[16];
bool first = true; // Vrednost koja oznacava da li se vrsi prvi pozi funkcije display ili ne
std::shared_ptr<Shape> objects[NUM_OF_OBJECTS]; // Niz objekata na sceni
std::map<Color, int> object_colors; // Mapira se boja u indeks u nizu objekata. Koristi se za selekciju.
int selected = -1; // Indeks objekta koji je selektovan
bool picked = false; // Indikator da li je korisnik nesto pokupio ili nije

void on_display();
void initialize();
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_mouse(int button, int s, int x, int y);
void on_motion(int x, int y); // Pomeraj misa dok je dugme selektovano
void on_passive_motion(int x, int y); // Pomeraj misa dok nijedno dugme nije selektovano

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("Shapes and colors");
//    glutFullScreen();

    initialize();

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);
    glutPassiveMotionFunc(on_passive_motion);

    glutMainLoop();

    return 0;
}

void initialize() {
    glClearColor(0, 0, 0, 0);

    /* Omogućava se provera dubine i normalizacija vektora normale */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Vrsi se inicijalizacija matrice rotacije na jedinicnu matricu */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}

void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /* U slučaju da korisnik pritisne esc program se zaustavlja */
            exit(0);
        case 'R': /* Pritiskom na R ili r se scena vraca na pocetnu */
        case 'r':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
            glutPostRedisplay(); // Forsira se ponovno iscrtavanje
            break;
    }
}

void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podešava se tačka pogleda */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 7, 0, 0, 0, 0, 1, 0);

    /* Primenjuje se matrica rotacije tako što se množi sa matricom za pogled i transformaciju */
    glMultMatrixf(rotation_matrix);

    /* Iscrtava se osnovna kocka */
    MainCube m;
    m.draw();

    if (first) {
        /* Prvi put se pravi niz objekata */

        srand(time(NULL));

        for (int i = 0; i < NUM_OF_OBJECTS; i++) {
            float size = ((float) rand() / (RAND_MAX)) * 0.5 + 0.4; // Uzima se slucajna velicia iz opsega [0.4, 0.9)

            /* Parametrizuje se krug na kom se nalaze objekti, kako bi se ravnomerno rasporedili */
            float t = i * (2 * M_PI) / NUM_OF_OBJECTS;
            float x = 4 * cos(t);
            float z = 4 * sin(t);
            Coordinates xyz = {x, 0, z};

            /* Bira se nasumicna vrsta objekta */
            int k = ((int) floor(((float) rand() / (RAND_MAX)) * 7) + i) % 7;
            switch (k) {
                case 0:
                    objects[i] = std::make_shared<Sphere>(xyz, size);
                    break;
                case 1:
                    objects[i] = std::make_shared<Cube>(xyz, size + 0.3);
                    break;
                case 2:
                    objects[i] = std::make_shared<TriangularPrism>(xyz, size + 0.4);
                    break;
                case 3:
                    objects[i] = std::make_shared<Cylinder>(xyz, size - 0.3);
                    break;
                case 4:
                    objects[i] = std::make_shared<Heart>(xyz, size + 0.4);
                    break;
                case 5:
                    size = ((float) rand() / (RAND_MAX)) * 0.2 + 0.25;
                    objects[i] = std::make_shared<Flower>(xyz, size);
                    break;
                case 6:
                    size = ((float) rand() / (RAND_MAX)) * 0.25 + 0.4;
                    objects[i] = std::make_shared<Star>(xyz, size);
                    break;
                default:
                    objects[i] = std::make_shared<Sphere>(xyz, size);
            }

            object_colors.insert(std::pair<Color, int>(objects[i]->_c, i));
            objects[i]->draw();
        }

        first = false;
    } else {
        for (int i = 0; i < NUM_OF_OBJECTS; i++) {
            objects[i]->draw();
        }
    }

    glutSwapBuffers();
}

void on_reshape(int width, int height) {
    window_h = height;
    window_w = width;

    /* Podešava se projekcija */
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_mouse(int button, int state, int x, int y) {
    /* U slučaju da je pritisnut levi taster miša pamti se pozicija*/
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouse_x = x;
        mouse_y = y;

        if(picked && selected != -1)
        {
            std::cout << "Proveravam da li stavlja na dobro mesto i ostavljam objekat tu" << std::endl;
            picked = false;
            return;
        }

        float pixel[3];
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_FLOAT, pixel);
        Color p = {pixel[0], pixel[1], pixel[2]};

        auto it = object_colors.cbegin();
        while(it != object_colors.cend())
        {
            if(!picked)
            {
                if (it->first == p) {
                    selected = it->second;
                    picked = true;
                    break;
                }
            }

            it++;
        }
    }
}

void on_motion(int x, int y) {
    int new_x, new_y;

    /* Izracunavaju se promene pozicije pokazivaca misa */
    new_x = x - mouse_x;
    new_y = y - mouse_y;

    mouse_x = x;
    mouse_y = y;

    /* Izracunava se nova matrica rotacije */
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (new_x < 0) {
        glRotatef(-180 * (float) new_x / window_w, 0, -1, 0);
    } else if (new_x > 0) {
        glRotatef(180 * (float) new_x / window_w, 0, 1, 0);
    } else if (new_y < 0) {
        glRotatef(180 * (float) new_y / window_h, 1, 0, 0);
    } else if (new_y > 0) {
        glRotatef(-180 * (float) new_y / window_h, -1, 0, 0);
    }

    glMultMatrixf(rotation_matrix);

    glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
    glPopMatrix();

    glutPostRedisplay();
}

void on_passive_motion(int x, int y) {
    if(picked)
    {

    }
}
