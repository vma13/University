/* gcc test.c -o test -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */

#include <stdlib.h>
#include <GL/glut.h>

GLint Width = 800, Height = 600;

void init() {
  
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
  glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
  glEnable(GL_LIGHTING);
}


void Display(void)
{

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-150, -50, 0);
    glVertex3f(250, -50, 0);
    
    glVertex3f(-150, -50, 0);
    glVertex3f(-150, 250, 0);
    
    glVertex3f(-150, -50, 0);
    glVertex3f(-150, -50, 250);
    glEnd();

    glutSolidSphere(150, 25, 25);

    glFlush();
}

void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1.0, 1.0);

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
    glutCreateWindow("Scene");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
