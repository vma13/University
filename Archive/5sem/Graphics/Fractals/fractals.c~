#include <GL/openglut.h>
#include "Stack.h"
#include <stdlib.h>
#include <math.h>
#define Angle 90.0

GLint Width = 700, Height = 600;
GLfloat a = 100;
GLfloat b = 350;
GLfloat Length = 6;
GLfloat cur_angle = 0.0;

void f(GLfloat *x, GLfloat *y) {
  glBegin(GL_LINES);
  glVertex2f(*x, *y);
  (*x) -= Length*cos(cur_angle*M_PI/180.0);
  (*y) += Length*sin(cur_angle*M_PI/180.0);
  glVertex2f(*x, *y);
  glEnd();
}

void Display(void) {
  struct stack *p;
  char c[40000] = {};
  FILE *file = fopen("out", "r");
  fscanf(file, "%s", c);
  fclose(file);
  glClearColor(1.0, 1.0, 1.0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  int i = 0;
  while( c[i] != '\0' ) {
    switch( c[i++] ) {
    case '+':
      cur_angle += Angle;
      if( cur_angle > 360.0 ) cur_angle -= 360.0;
      break;
    case '-':
      cur_angle -= Angle;
      break;
    case 'F':
      f(&a, &b);
      break;
    case '[':
      push(a, b, cur_angle);
      break;
    case ']':
      p = pop();
      a = p->x;
      b = p->y;
      cur_angle = p->angle;
      break;
    }
  }
  glFinish();
}

void Reshape(GLint w, GLint h) {
  Width = w;
  Height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, 0, h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
#define ESCAPE '\033'
  if( key == ESCAPE ) exit( 0 );
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Width, Height);
  if( !(glutCreateWindow("Fractals")) ) {
    fprintf(stderr, "%s", "Can't create window..");
    exit( 1 );
  }
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
  return 0;
}
