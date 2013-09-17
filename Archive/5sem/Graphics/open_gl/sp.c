#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLint Width = 800, Height = 800;
GLint xc = 0, yc = 0, zc = 0;

GLfloat cur_x = 0, cur_y = 0;
GLfloat X = 0, Y = 0;
GLdouble cam_x = 1.0, cam_y = 1.0;


void init(void)
{
  GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[]={50.0};
  GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};
  GLfloat white_light[]={1.0, 1.0, 1.0, 1.0};
  GLfloat blue_light[]={0.0, 1.0, 1.0, 1.0};
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  gluLookAt(cam_x, cam_y, 1, 0, 0, 0, 0, 1, 0);
  
  glDisable (GL_LIGHTING);
  
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3f(xc, yc, zc);
  glVertex3f(Width, yc, zc);
  
  glVertex3f(xc, yc, zc);
  glVertex3f(xc, Height, zc);
  
  glVertex3f(xc, yc, zc);
  glVertex3f(xc, yc, 250);
  glEnd();

  //glPushMatrix();
  //glTranslatef(2, 0, 0);
  glRotatef(X, 0, 1, 0);
  glRotatef(Y, 1, 0, 0);
  glEnable(GL_LIGHTING);
   
  glutSolidSphere(0.3, 20, 16);
  //glutSolidCube(0.5);

  glPopMatrix();
  
  glutSwapBuffers();
}
void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5,- 10.0, 10.0);
  //gluLookAt(cam_x, cam_y, 1, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
  if( key == ESCAPE )
    exit(0);
}

void Arrows(int key, int x, int y) {
  switch(key) {
  case 100:
    cam_x -= .01;
    break;
    //case GLUT_KEY_RIGHT:
    //cam_x += .01;
    //break;
  }
  glutPostRedisplay();
  printf("%d\n", key);
}

void motion(int x, int y) {
  if(cur_x == 0 && cur_y == 0) {
    cur_x = x;
    cur_y = y;
    printf("!!!\n");
    return;
  }
  float xx = x, yy = y;
  X = (cur_x - (float)xx);
  Y = (cur_y - (float)yy);
  //cur_x = xx;
  //cur_y = yy;
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Rendering a Lit Sphere");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Arrows);
  glutMotionFunc(motion);
  glutMainLoop();
  return 0;
}
