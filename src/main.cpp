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

#define FILENAME0 "images/tekstura_kutije.bmp"
#define TIMER0 0
#define TIMER1 1
#define TIMER_INTERVAL0 50
#define TIMER_INTERVAL1 100

int window_w, window_h; // Pri promeni pamti se širina i visina prozora
int mouse_x = 0, mouse_y = 0; // Pri promeni pamti se pozicija miša
float rotation_matrix[16];
float selection_matrix[16];
bool first_draw = true; // Vrednost koja oznacava da li se vrsi prvi pozi funkcije display ili ne
extern std::shared_ptr<Shape> objects[NUM_OF_OBJECTS]; // Niz objekata na sceni
GLuint names[2]; // Identifikatori tekstura
float scale = 1; // Promenljiva koja se koristi za zumiranje
int current_object = 0; // Indeks trenutno selektovanog objekta
int current_shape_on_cube = 10;
bool animation_ongoing0 = false;
float delta = 0.1;
float delta_y = 0;
bool animation_ongoing1 = false;
float angle = 30;
float rotation = 0;
bool matched = false;
extern std::map<int, bool> matched_objects;

void on_display();
void initialize();
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_mouse(int button, int s, int x, int y);
void on_motion(int x, int y); // Pomeraj misa dok je dugme selektovano
void on_special(int key, int x, int y); // Registruju se pritisci na strelice na tastaturi
void on_timer0(int value);
void on_timer1(int value);

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
    glutSpecialFunc(on_special);

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
        case 32:
            if(animation_ongoing0)
            {
                animation_ongoing0 = false;
                delta_y = 0;
                objects[current_object]->_xyz.y = 0;
                glutPostRedisplay();
                animation_ongoing1 = true;
                glutTimerFunc(TIMER_INTERVAL0, on_timer1, TIMER1);
            }
            else
            {
                if(current_shape_on_cube == current_object)
                {
                    matched = true;
                    glutPostRedisplay();
                }

                animation_ongoing1 = false;
                rotation = 0;
                animation_ongoing0 = true;
                current_shape_on_cube = (current_shape_on_cube + 10) % 20;
                glutTimerFunc(TIMER_INTERVAL1, on_timer0, TIMER0);
            }
            break;
    }
}

void on_special(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_RIGHT:
            if(animation_ongoing0)
            {
                objects[current_object]->_xyz.y = 0;
                current_object++;
                if(current_object >= NUM_OF_OBJECTS)
                    current_object = 0;

                while(matched_objects[current_object])
                {
                    current_object++;
                    if(current_object >= NUM_OF_OBJECTS)
                        current_object = 0;
                }
            }
            else if(animation_ongoing1)
            {
                rotation = 0;
                current_shape_on_cube++;
                if(current_shape_on_cube >= NUM_OF_OBJECTS)
                    current_shape_on_cube = 0;

                while(matched_objects[current_shape_on_cube])
                {
                    current_shape_on_cube++;
                    if(current_shape_on_cube >= NUM_OF_OBJECTS)
                        current_shape_on_cube = 0;
                }
            }
            break;
        case GLUT_KEY_LEFT:
            if(animation_ongoing0)
            {
                objects[current_object]->_xyz.y = 0;
                current_object--;
                if(current_object <= 0)
                    current_object = NUM_OF_OBJECTS-1;

                while(matched_objects[current_object])
                {
                    current_object--;
                    if(current_object <= 0)
                        current_object = NUM_OF_OBJECTS-1;
                }
            }
            else if(animation_ongoing1)
            {
                rotation = 0;
                current_shape_on_cube--;
                if(current_shape_on_cube <= 0)
                    current_shape_on_cube = NUM_OF_OBJECTS-1;

                while(matched_objects[current_shape_on_cube])
                {
                    current_shape_on_cube--;
                    if(current_shape_on_cube <= 0)
                        current_shape_on_cube = NUM_OF_OBJECTS-1;
                }
            }
            break;
        case GLUT_KEY_UP:
            scale += 0.2;
            scale = scale > 2.4? 2.4 : scale;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            scale -= 0.2;
            scale = scale < 0.4? 0.4 : scale;
            glutPostRedisplay();
            break;
    }
}

void on_timer0(int value)
{
    if(value != TIMER0)
        return;

    delta_y += delta;
    if(delta_y >= 1 || delta_y <= -1)
        delta *= -1;

    glutPostRedisplay();

    if(animation_ongoing0)
        glutTimerFunc(TIMER_INTERVAL0, on_timer0, TIMER0);
}

void on_timer1(int value)
{
    if(value != TIMER1)
        return;

    rotation += angle;
    if(rotation == 360)
        rotation = 0;

    glutPostRedisplay();

    if(animation_ongoing1)
        glutTimerFunc(TIMER_INTERVAL1, on_timer1, TIMER1);
}

void on_display() {
    /* Podešava se svetlo */

    /* Boje svetla */
    GLfloat light_position[] = { 0, 5, 0, 0 };
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
        first.initialize_objects();

        first_draw = false;

        animation_ongoing0 = true;
        glutTimerFunc(500, on_timer0, TIMER0);
    }

    for (int i = 0; i < NUM_OF_OBJECTS; i++)
    {
        if(matched_objects[i])
            continue;

        if(i == current_object && matched)
        {
            objects[i] = nullptr;

            matched_objects[i] = true;
            current_object++;
            matched = false;
            continue;
        }

        if(objects[i] != nullptr)
        {
            if(i == current_object && animation_ongoing0)
            {
                Coordinates object_coordinates = objects[i]->_xyz;
                object_coordinates.y = delta_y;
                objects[i]->_xyz = object_coordinates;
                objects[i]->draw(objects[i]->getC());

                glPushMatrix();
                /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
                Coordinates xyz = places_on_main_cube.find(objects[i]->getId())->second;
                glTranslatef(xyz.x, xyz.y, xyz.z);

                objects[i]->draw_on_main_cube(objects[i]->getC());
                glPopMatrix();
            }
            else if(i == current_shape_on_cube && animation_ongoing1)
            {
                objects[i]->draw(objects[i]->getC());

                glPushMatrix();
                /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
                Coordinates xyz = places_on_main_cube.find(objects[i]->getId())->second;
                glTranslatef(xyz.x, xyz.y, xyz.z);

                switch(objects[i]->getId() % 3)
                {
                    case 0:
                        glRotatef(rotation, 0, 0, 1);
                        break;
                    case 1:
                        glRotatef(rotation, 1, 0, 0);
                        break;
                    case 2:
                        glRotatef(rotation, 0, 1, 0);
                        break;
                    default: std::cerr << "This should not happen" << std::endl;
                }

                objects[i]->draw_on_main_cube(objects[i]->getC());
                glPopMatrix();
            }
            else
            {
                objects[i]->draw(objects[i]->getC());

                glPushMatrix();
                /* Na osnovu id-ja u mapi se pronalazi odgovarajuća pozicija na kocki */
                Coordinates xyz = places_on_main_cube.find(objects[i]->getId())->second;
                glTranslatef(xyz.x, xyz.y, xyz.z);

                objects[i]->draw_on_main_cube(objects[i]->getC());
                glPopMatrix();
            }

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


void on_mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        /* U slučaju da je pritisnut levi taster miša pamti se pozicija*/
        mouse_x = x;
        mouse_y = y;
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
