#include <stdlib.h>
#include <GL/glut.h>
GLint Width = 800, Height = 800;

GLfloat tmp = 0, tmp1 = 45, tmp2 = 150, tmp3 = 150, tmp4 = 0;

void init(void)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_FLAT);
  glClearColor(0.0,0.0,0.0,0.0);
}

void Display(void){
  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  //верхняя
  glPushMatrix();
  glColor4f(255,0,0,0.3); 
  glTranslatef(0.0, 295.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidCone(100, 300, 40, 4);
  glPopMatrix();
  
  //нижняя
  glPushMatrix();
  glColor4f(255,0,0,0.3);
  glTranslatef(0.0, -295.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutSolidCone(100.0, 300, 40, 4);
  glPopMatrix();
  
  //которая уменьшается
  glPushMatrix();
  glColor4f(255,255,0,0.3); 
  glTranslatef(0.0,(GLfloat)tmp3,0.0);
  glRotatef(90.0, 100.0, 1.0, 0.0);
  //glutSolidCone((GLfloat)tmp1,(GLfloat)tmp2, 40, 4);
  glutSolidCone((GLfloat)tmp1,(GLfloat)tmp2,40,4);
  glPopMatrix();
  
  //которая из низа выростает
  glPushMatrix();
  glColor4f(255.0, 255.0, 0.0, 0.3);
  glTranslatef(0.0,-295.0,0.0);
  glRotatef(-90, 1.0,0.0,0.0);
  glutSolidCone(60,(GLfloat)tmp4,40,4);
  glPopMatrix();
  
  //песчинка
  glPushMatrix();
  glColor4f(255,255,0,0.3); 
  glTranslatef(0.0, -(GLfloat)tmp, 0.0);
  //glRotatef(0, 1.0, 0.0, 0.0);
  glutSolidSphere(3, 40, 40);
  glPopMatrix();
  
  glFlush();
  glutSwapBuffers();
}

void Reshape(GLint w, GLint h)
{
  Width = w;
  Height = h;
  
    glViewport(0, 0, w, h);
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width, Width, -Height, Height, -512.0, 512.0);
    //gluLookAt(7.0, -2.0, 5.03, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
}

void idle() {
  
  tmp += 5;
  tmp3 -= 0.4;//0.038;
  tmp4 += 0.1;//0.04;
  if(tmp2>0){
      tmp1 -= 0.14;//0.012;
  tmp2 -= 0.4;//0.04;
  }
    
  if(tmp > 300){
    tmp = 0;
  }
  
   glutPostRedisplay();
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
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("CLOCK");
  glutIdleFunc(idle);
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
}

