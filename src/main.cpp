#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include "mainCube.hpp"
#include "../shapes/shapes.hpp"
#include "firstScene.hpp"
#include "texture.hpp"

#define TIMER_ID 0
#define FILENAME0 "images/tekstura_kutije.bmp"

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
GLuint names[2]; // Identifikatori tekstura
float scale = 1; // Promenljiva koja se koristi za zumiranje

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
//    glutFullScreen();

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

    glShadeModel(GL_SMOOTH);

    /* Vrsi se inicijalizacija matrice rotacije i matrice selekcije na jedinicnu matricu */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);

    Texture image; // Objekat koji predstavlja teksturu učitanu iz fajla

    /* Uključuju se teksture */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /* Kreira se prva tekstura */
    image.read(FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image.getWidth(), image.getHeight(), 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image.getPixels());

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    image.free_image();
}

void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /* U slučaju da korisnik pritisne esc program se zaustavlja */
            glDeleteTextures(2, names);
            exit(0);
        case 'R': /* Pritiskom na R ili r se scena vraca na pocetnu */
        case 'r':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
            glutPostRedisplay(); // Forsira se ponovno iscrtavanje
            break;
        case 'w':
        case 'W':
            scale += 0.2;
            scale = scale > 2.4? 2.4 : scale;
            glutPostRedisplay();
            break;
        case 's':
        case 'S':
            scale -= 0.2;
            scale = scale < 0.4? 0.4 : scale;
            glutPostRedisplay();
            break;
    }
}

void on_display() {
    /* Podešava se svetlo */

    /* Boje svetla */
    GLfloat light_position[] = { -2, 5, 0, 0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 0.1 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1 };

    /* Koeficijenti refleksije svetla */
    GLfloat shininess = 50;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podešava se tačka pogleda */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 7, 0, 0, 0, 0, 1, 0);

    /* Primenjuje se matrica rotacije tako što se množi sa matricom za pogled i transformaciju */
    glMultMatrixf(rotation_matrix);
    glScalef(scale, scale, scale);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /* Iscrtava se osnovna kocka */
    glBindTexture(GL_TEXTURE_2D, names[0]);
        MainCube m;
        m.draw();
    glBindTexture(GL_TEXTURE_2D, 0);

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
            std::cout << "r(" << pixel[0] << " ," << pixel[1] << ", " << pixel[2] << ")" << std::endl;
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
