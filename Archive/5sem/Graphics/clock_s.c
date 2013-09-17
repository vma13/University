#include <stdlib.h>
#include <GL/glut.h>
GLint Width = 800, Height = 800;

GLfloat speed_sand = 0, u_radius = 0.065, l_radius = 0, u_high = 0.195, l_high = 0, high_change = 0;

void init(void)
{
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glShadeModel(GL_FLAT);
glClearColor(0.0,0.0,0.0,0.0);
}
       
void Display(void){

  
  GLUquadricObj *quadObj;
  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix(); //верхняя чаша
  glColor4f(255,0,0,0.3); 
  glTranslatef(0.0, 0.295, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidCone(0.1, 0.3, 40, 4);
  glPopMatrix();

  glPushMatrix();// нижная чаша
  glColor4f(255,0,0,0.3);
  glTranslatef(0.0, -0.295, 0.0);
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glutSolidCone(0.1, 0.3, 40, 4);
  glPopMatrix();
  
  glPushMatrix();// верхний песочек
  glColor4f(255,255,0,0.3); 
  glTranslatef(0.0,(0.2+(GLfloat)high_change),0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glutSolidCone((GLfloat)u_radius,(GLfloat)u_high, 40, 4);
  glPopMatrix();
    
  glPushMatrix(); // нижний песочек
  glColor4f(255,255,0,0.3); 
  glTranslatef(0.0,-0.295,0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  glutSolidCone((GLfloat)l_radius,(GLfloat)l_high, 40, 4);
  glPopMatrix();
  
  glPushMatrix();
  glColor4f(255,255,0, 0.1); 
  glTranslatef(0.0, -(GLfloat)speed_sand, 0.0);
  glutSolidSphere(0.003, 40, 40);
  glPopMatrix();
  
  glPushMatrix(); // правая опора
  glColor4f(0.0, 255, 255, 1.0);
  glTranslatef(0.115, -0.295, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluCylinder(quadObj, 0.015, 0.015, 0.59, 40, 40);
  glPopMatrix();
  
  glPushMatrix();// левая опора
  glColor4f(0.0, 255, 255, 1.0);
  glTranslatef(-0.115, -0.295, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluCylinder(quadObj, 0.015, 0.015, 0.59, 40, 40);
  glPopMatrix();
  
  glPushMatrix();//хрен знает что
  glColor4f(0.0, 255, 255, 1.0);
  glTranslatef(0.0, 0.295, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluDisk(quadObj, 0.0, 0.15, 10, 10);
  glPopMatrix();
  
  glPushMatrix();//верхняя планка
  glColor4f(0.0, 255, 0, 1.0);
  glTranslatef(0.0, 0.295, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluCylinder(quadObj, 0.15, 0.15, 0.03, 40, 40);
  glPopMatrix();
  
  glPushMatrix();//хрен знает что 2
  glColor4f(0.0, 255, 255, 1.0);
  glTranslatef(0.0, 0.298, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluDisk(quadObj, 0.0, 0.15, 10, 10);
  glPopMatrix();
  
  glPushMatrix();//нижняя планка
  glColor4f(0.0, 255, 255, 1.0);
  glTranslatef(0.0, -0.325, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  gluCylinder(quadObj, 0.15, 0.15, 0.03, 40, 40);
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
    glOrtho(-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5,- 10.0, 10.0);
    //gluLookAt(1.0, 0.3, 1.0, 0, 0, 0, 0, 1, 0);
    
}

void idle() {
  
  
  if(u_radius > 0){
    u_radius -= 0.00001;
    u_high -= 0.00003;
  }
  if(l_radius < 0.1){
  l_radius += 0.000015;
  l_high += 0.00002;
  speed_sand += 0.001;
    if(l_radius >= 0.1){
     speed_sand = 0.295;
    }
  }
  if(0.2-high_change > 0) {
  high_change -=0.00003;
  }
   if((speed_sand > (0.295-l_high)) && (l_radius < 0.1)){
   speed_sand = 0;
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
    glutCreateWindow("Sand Clock");
    glutIdleFunc(idle);
    init();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}

