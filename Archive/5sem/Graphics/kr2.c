/* gcc test.c -o test -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

/* подключаем библиотеку GLUT */
#include <GL/glut.h>

/* начальная ширина и высота окна */
GLint Width = 800, Height = 800;

/* эта функция управляет всем выводом на экран */
GLint size_cube = 100;
void Display(void){

glClear(GL_COLOR_BUFFER_BIT);
 
glColor3ub (200, 0, 55);

 glPushMatrix();
 glutSolidCube(size_cube);
 glPopMatrix();

 

 glColor3ub (0, 100, 120);

 glBegin(GL_LINES);
 glVertex3f(0,0,0);
 glVertex3f(0, 750, 0);
 glEnd();

  glBegin(GL_LINES);
 glVertex3f(0, 0, 0);
 glVertex3f(0, 0, 750);
 glEnd();

  glBegin(GL_LINES);
 glVertex3f(0,0,0);
 glVertex3f(750, 0, 0);
 glEnd();

      

 glFlush();
 
}


/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
     Width = w;
    Height = h;

    glViewport(0, 0, w, h);

   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width, Width, -Height, Height, -512.0, 512.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(170.0, 150.0, 150.0,  /* eye */
                0.0, 0.0, 0.0,  /* center */
              0.0, 1.0, 0.0); /* positive direction */
    
}


/* Функция обрабатывает сообщения от клавиатуры */

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

    if( key == ESCAPE )
      exit(0);
    switch(key){
    case 32 :
      size_cube += 100;
      break;
    case 'h':
      size_cube -= 100;
      break;

    default:
      break;
    }
    glutPostRedisplay();
}

/* Главный цикл приложения */
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Sphere");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
