#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>


#include <GL/glut.h>


GLint Width = 800, Height = 800;

//GLfloat rat;


void Display(void){

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(255,0,0);
  //bottom cone
  glPushMatrix(); 
  glTranslatef(0.0, -590.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutSolidCone(150, 300, 40, 4);
  glPopMatrix();
  //top cone
  glPushMatrix();
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidCone(150, 300, 40, 4);
  glPopMatrix();
  //top sand
  glColor3ub(255, 255, 0);
  glPushMatrix();
  glTranslatef(0.0, -590.0, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutSolidCone(50, 100, 20, 4);
  glPopMatrix();
  //bottom sand
  glPushMatrix();
  glTranslatef(0.0, -100.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidCone(100, 200, 40, 4);
  glPopMatrix();
  //sand
  glColor3ub(0, 0, 255);
  glPushMatrix();
  glTranslatef(0.0, -320.0, 0.0);
  //glTranslatef(0.0, (GLfloat)rat, 0.0);
  glutSolidSphere(5,10,10);
  glPopMatrix();
  //animation();

    
 glFlush();
 
}

/*void animation(){
  rat += 10.0;
  glutPostRedisplay();
  }*/


void Reshape(GLint w, GLint h)
{
     Width = w;
    Height = h;

    glViewport(0, 0, w, h);

   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width, Width, -Height, Height, -512.0, 512.0);
    gluLookAt(2.0, 2.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
    
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
    glutCreateWindow("Sand Clock");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
