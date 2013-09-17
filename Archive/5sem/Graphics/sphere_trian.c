#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLint Width = 500, Height = 500;

GLfloat speed_start, speed_stop = 0;
//For Sphere:
GLfloat mat_specular_sphere[] = {0.3, 0.3, 0.3, 1.0};
GLfloat mat_defuse_sphere[] = {0.0, 0.7, 0.7, 1.0};
GLfloat mat_shininess_sphere[] = {10.0};
//For Triangle 1:
GLfloat mat_specular_tri_1[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_defuse_tri_1[] = {0.5, 0.2, 0.2, 1.0};
GLfloat mat_shininess_tri_1[] = {128.0};
GLfloat mat_ambient_tri_1[] = {0.9, 0.9, 0.9, 1.0};
//For Triangle 2:
GLfloat mat_specular_tri_2[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_defuse_tri_2[] = {1.0, 0.2, 0.2, 1.0};
GLfloat mat_shininess_tri_2[] = {128.0};
GLfloat mat_ambient_tri_2[] = {0.9, 0.9, 0.9, 1.0};

float Angle1 = 0;
float Angle2 = 0;
int camXAngle = 0;
int camYAngle = 0;
float camMove = 0.0;
float camMax = -0.4;
float camMin = 20.0;
float scale = 1;

float speed = 0.5;

void init(void)
{

  GLfloat light_position[] = {15.0, -2.0, 20.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void InitCam(){
  glRotatef((GLfloat)camYAngle, 1.0, 0.0, 0.0);
  glRotatef((GLfloat)camXAngle, 0.0, 1.0, 0.0);
}

void display(void)
{
  
  glPushMatrix();
  
  glScalef(scale,scale,scale);
  glEnable(GL_NORMALIZE);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_sphere);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse_sphere);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_sphere);
  InitCam();
  glutSolidSphere(0.4, 100, 100);
  glPushMatrix();
  
  glRotatef((GLfloat)speed_start, 0.0, 0.0, 1.0);
  glTranslatef(0.4, 0.0, 0.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse_tri_1);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_tri_1);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_tri_1);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_tri_1);
  
  glutSolidCone(0.1, 0.3, 4, 1);
  glPopMatrix();
  
  
  glPushMatrix();
  glRotatef((GLfloat)speed_stop, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.4, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse_tri_2);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_tri_2);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_tri_2);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_tri_2);

  glutSolidCone(0.1, 0.3, 4, 1);
  glPopMatrix();
  glPopMatrix();
  glutSwapBuffers();
}


void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5,- 10.0, 10.0);
  gluLookAt(0.5, -0.1, 1.8, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void idle() {
  speed_start += speed;
  speed_stop -= speed;
  Angle1 += 0.5;
  Angle2 -= 0.3;

  if(Angle1 >= 360.0){
    Angle1 -= 360.0;
  }

  if(Angle2 >= 360.0){
    Angle2 -= 360.0;
  }

  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
  
  if( key == ESCAPE )
    exit(0);
  switch(key)
  {
  case 'p':
    speed = 0.5;
    break;
    
  case 'o':
    speed = 0;
    break;

  case 'k':        //increase rotation speed 
    speed += 0.5;
    break;

  case 'l':        //decrease rotation speed 
    speed -= 0.5;
    break;
  
    case '+':
      if(scale < 3){
      scale += 0.2;
      }
    break;
    
    case '-':
      if(scale > 0.2){
      scale -= 0.1;
      }
    break;
    
    default:
    break;
  }
  glutPostRedisplay();
}

void Keys(int key, int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      camYAngle += 5;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_RIGHT:
      camXAngle -= 5.0;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_LEFT:
      camXAngle += 5.0;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_DOWN:
      camYAngle -= 5.0;
      glutPostRedisplay();
    break;
    
    default:
    break;
  }
}


int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Sphere & triangles");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Keys);
  glutMainLoop();
  return 0;
}
