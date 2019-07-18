#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>

void on_display();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);

    glClearColor(0.75, 0.75, 0.75, 0);

    glutMainLoop();

    return 0;
}

void on_display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(-0.5, 0.5, 0);
    glVertex3f(0.5, 0.5, 0);
    glEnd();

    glutSwapBuffers();
}
