#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "mainCube.hpp"
#include "shapes.hpp"

int window_w, window_h; // Pri promeni pamti se širina i visina prozora
int mouse_x = 0, mouse_y = 0; // Pri promeni pamti se pozicija miša
float rotation_matrix[16];

void on_display();
void initialize();
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_mouse(int button, int s, int x, int y);
void on_motion(int x, int y);

int main(int argc, char **argv)
{
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

void initialize()
{
    glClearColor(0, 0, 0, 0);

    /* Omogućava se provera dubine i normalizacija vektora normale */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Vrsi se inicijalizacija matrice rotacije na jedinicnu matricu */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: /* U slučaju da korisnik pritisne esc program se zaustavlja */
            exit(0);
        case 'R':
        case 'r': glMatrixMode(GL_MODELVIEW);
                  glLoadIdentity();
                  glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
                  glutPostRedisplay();
                  break;
    }
}

void on_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podešava se tačka pogleda */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 6, 0, 0, 0, 0, 1, 0);

    /* Primenjuje se matrica rotacije tako što se množi sa matricom za pogled i transformaciju */
    glMultMatrixf(rotation_matrix);

    /* Iscrtava se osnovna kocka */
    MainCube m;
    m.draw();

    /* Ponovo se podesava pogled i matrica postavlja na jediničnu da se ne bi objekti rotirali sa kockom zajedno */
    //glLoadIdentity();
    //gluLookAt(0, 3, 6, 0, 0, 0, 0, 1, 0);

    /* TODO: dodati objekte*/

    glutSwapBuffers();
}

void on_reshape(int width, int height)
{
    window_h = height;
    window_w = width;

    /* Podešava se projekcija */
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (float)width/height, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void on_mouse(int button, int s, int x, int y)
{
    /* U slučaju da je pritisnut levi taster miša pamti se pozicija*/
    if(button == GLUT_LEFT_BUTTON)
    {
        mouse_x = x;
        mouse_y = y;
    }
}

void on_motion(int x, int y)
{
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

        if(new_x < 0)
        {
            glRotatef(-180 * (float)new_x/window_w, 0, -1, 0);
        }
        else if(new_x > 0)
        {
            glRotatef(180 * (float)new_x/window_w, 0, 1, 0);
        }
        else if(new_y < 0)
        {
            glRotatef(180 * (float)new_y/window_h, 1, 0, 0);
        }
        else if(new_y > 0)
        {
            glRotatef(-180 * (float)new_y/window_h, -1, 0, 0);
        }

        glMultMatrixf(rotation_matrix);

        glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
    glPopMatrix();

    glutPostRedisplay();
}