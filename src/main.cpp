#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include "mainCube.hpp"
#include "shapes.hpp"
#include "firstScene.hpp"

#define TIMER_ID 0

int window_w, window_h; // Pri promeni pamti se širina i visina prozora
int mouse_x = 0, mouse_y = 0; // Pri promeni pamti se pozicija miša
float rotation_matrix[16];
float selection_matrix[16];
bool first_draw = true; // Vrednost koja oznacava da li se vrsi prvi pozi funkcije display ili ne
extern std::shared_ptr<Shape> objects[NUM_OF_OBJECTS]; // Niz objekata na sceni
extern std::map<Color, int> object_colors; // Mapira se boja u indeks u nizu objekata. Koristi se za selekciju.
extern std::map<Color, int> object_colors_on_cube; // Mapira se boja u indeks u nizu objekata za objekte na glavnoj kocki. Koristi se za selekciju.
int selected_object = -1; // Indeks objekta koji je selektovan
bool waiting_for_another_click = false; // Koristi se za registrovanje dvoklika

void on_display();
void initialize();
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_mouse(int button, int s, int x, int y);
void on_motion(int x, int y); // Pomeraj misa dok je dugme selektovano
void on_timer(int value); // Tajmer za registrovanje dvoklika

extern std::map<int, Coordinates> places_on_main_cube;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("Shapes and colors");
    glutFullScreen();

    initialize();

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);

    glutMainLoop();

    return 0;
}

void initialize() {
    glClearColor(0, 0, 0, 0);

    /* Omogućava se provera dubine i normalizacija vektora normale */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Vrsi se inicijalizacija matrice rotacije i matrice selekcije na jedinicnu matricu */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);

    get_coordinates(); // Koordinate na kocki
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

    if (first_draw)
    {
        /* Prvi put se pravi niz objekata */
        FirstScene first = FirstScene::getInstance();
        first.draw();

        first_draw = false;
    } else {
        for (auto& object : objects) {
            object->draw();

            float r = object->_c.color_r - 0.01;
            float g = object->_c.color_g - 0.01;
            float b = object->_c.color_b - 0.01;

            Color c = {r, g, b};

            object->draw_on_main_cube(c);
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

void on_timer(int value)
{
    if(value != TIMER_ID)
        return;

    waiting_for_another_click = false;
}

void on_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        /* U slučaju da je pritisnut levi taster miša pamti se pozicija*/
        mouse_x = x;
        mouse_y = y;

        /* Dvoklikom na ojbekte se oni selektuju*/
        if(!waiting_for_another_click)
        {
            waiting_for_another_click = true;
            glutTimerFunc(250, on_timer, TIMER_ID);
            return;
        }

        if(waiting_for_another_click)
        {
            float pixel[3];
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            /* Ako je nešto selektovano, proverava se samo da li je sledeći selektovani objekat na kocki;
             * ako nije zna se da je greška u pitanju. Kada ništa nije selektovano promenljiva
             * selected_object ima vrednost -1. */
            if(selected_object != -1)
            {
                glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_FLOAT, pixel);
                Color p = {pixel[0], pixel[1], pixel[2]};
                std::cout << "r(" << pixel[0] << " ," << pixel[1] << ", " << pixel[2] << ")" << std::endl;

                int selected = -1;
                auto it = object_colors_on_cube.cbegin();
                while(it != object_colors_on_cube.cend())
                {
                    if (it->first == p)
                    {
                        selected = it->second;
                        std::cout << selected_object << std::endl;
                        break;
                    }

                    it++;
                }

                if(selected != -1) {
                    std::cout << "Proveravam da li su upareni" << std::endl;
                    selected_object = -1;
                }
                else {
                    selected_object = -1;
                    std::cout << selected_object << std::endl;
                }

                return;
            }

            glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_FLOAT, pixel);
            Color p = {pixel[0], pixel[1], pixel[2]};

            auto it = object_colors.cbegin();
            while(it != object_colors.cend())
            {
                if(selected_object == -1)
                {
                    if (it->first == p) {
                        selected_object = it->second;

                        glMatrixMode(GL_MODELVIEW);
                        glPushMatrix();
                            glLoadMatrixf(objects[selected_object]->_system);
                            glGetFloatv(GL_MODELVIEW_MATRIX, selection_matrix);
                            std::cout << selected_object << std::endl;
                        glPopMatrix();
                        break;
                    }
                }

                it++;
            }
        }
    }
}

/* Držanjem pritisnutog levog tastera miša rotira se glavna kocka sa objektima */
void on_motion(int x, int y) {
    int new_x, new_y;

    /* Izracunavaju se promene pozicije pokazivaca miša */
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
