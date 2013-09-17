/* gcc test.c -o test -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */

#include <stdlib.h>
#include <GL/glut.h>

GLint Width = 640, Height = 480;


void Display(void)
{
    int left, right, top, bottom;

    left  = (Width - CubeSize) / 2;
    right = left + CubeSize;
    bottom = (Height - CubeSize) / 2;
    top = bottom + CubeSize;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(.8f, .8f, 0.0f);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(100, 0, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0,100, 0);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 100);
    glEnd();

    glFinish();
}

void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);
}

main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Red square example");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
