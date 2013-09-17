/* gcc test.c -o test -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

#define LL 20

#define ANGLE -15

GLint Width = 800, Height = 800;

GLfloat cur_x, cur_y, cur_angle;

struct stack {
  GLfloat x, y, angle;
  struct stack *next;
} stack;

struct stack *head = NULL;

void push() {
  struct stack *p;
  if((p = malloc(sizeof(struct stack))) == NULL)
    exit(1);
  p->x = cur_x;
  p->y = cur_y;
  p->angle = cur_angle;
  p->next = head;
  head = p;
}

void pop() {
  struct stack *p = head;
  cur_x = head->x;
  cur_y = head->y;
  cur_angle = head->angle;
  head = head->next;
  free(p);
}

void F() {
  GLfloat new_x, new_y;
  new_x = cur_x + LL * cos(cur_angle*M_PI/180);
  new_y = cur_y + LL * sin(cur_angle*M_PI/180);
  glBegin(GL_LINES);
  glVertex2f(cur_x, cur_y);
  glVertex2f(new_x, new_y);
  glEnd();
  cur_x = new_x;
  cur_y = new_y;
}

void Draw() {
  FILE *file;
  char *buf;
  int i;
  int size;
  if((file = fopen("out", "r")) == NULL) exit(1);
  fseek(file, 0, SEEK_END);
  size = ftell(file) + 1;
  buf = (char*)malloc(size*sizeof(char));
  rewind(file);
  fgets(buf, size, file);
  close(file);
  for(i = 0; i < size; i++) {
    if(buf[i] == '+') {
      cur_angle += ANGLE;
      if(cur_angle > 360) cur_angle -= 360;
      continue;
    }
    if(buf[i] == '-') {
      cur_angle -= ANGLE;
      if(cur_angle < -360) cur_angle += 360;
      continue;
    }
    if(buf[i] == 'F') {
      F();
      continue;
    }
    if(buf[i] == '[') {
      push();
      continue;
    }
    if(buf[i] == ']') {
      pop();
      continue;
    }
  }
  free(buf);
}

void Display(void)
{
  cur_x = Width/2;
  cur_y = Height/2;
  cur_angle = 0;

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(0.0, 0.0, 0.0);

  Draw();
  
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
  glutCreateWindow("Turtle Draw");
  
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  
  glutMainLoop();
}
