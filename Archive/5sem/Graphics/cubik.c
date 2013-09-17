#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLint Width = 800, Height = 600;
GLint flag = 0;
 
GLfloat sc_matrix[16] = {
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 0.01
};

GLfloat tr_matrix[16] = {
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  50.0, 0.0, 0.0, 1.0
};

void display(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(Width/2, 0, 0);
    glColor3f(0, 1, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Height/2, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, Width/2);
  glEnd();
  
  glPushMatrix();
  glColor3f(1, 0, 0);
  glRotatef(-45, 1, 0, 0);
  glTranslatef(50, 0, 0);
  glScalef(100, 100, 100);
  glTranslatef(0.5, 0.5, .5);
  glutWireCube(1);
  glPopMatrix();
  glFlush();
}

void display2(void) {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glBegin(GL_LINES);
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(Width/2, 0, 0);
    glColor3f(0, 1, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Height/2, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, Width/2);
  glEnd();
  glColor3f(0, 0, 1);
  glPushMatrix();
  GLfloat rt_matrix[16] = {
    1, 0, 0, 0,
    0, 0.707106, 0.707106, 0,
    0, -0.707106, 0.707106,0,
    0, 0, 0, 1
  };
  rt_matrix[5] = cos(45.0*M_PI/180);
  rt_matrix[6] = -sin(45.0*M_PI/180);
  rt_matrix[9] = sin(45.0*M_PI/180);
  rt_matrix[10] = cos(45.0*M_PI/180);
  
  glMultMatrixf(rt_matrix);
  glMultMatrixf(tr_matrix);
  glMultMatrixf(sc_matrix);
  glTranslatef(0.5, 0.5, .5);
  glutWireCube(1.0);
  glPopMatrix();
  glFlush();
}


void reshape(GLint w, GLint h) {
  Width = w;
  Height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, w/h, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(200.0, 200.0, 270.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
  if( key == 32 ) {
    if(flag == 1) { 
      glutDisplayFunc(display);
      flag = 0;
    }
    else {
      glutDisplayFunc(display2);
      flag = 1;
    }
    glutPostRedisplay();
  }
  if( key == '\033' )
    exit( EXIT_SUCCESS );
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("Cube");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return EXIT_SUCCESS;
}
