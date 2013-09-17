#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glext.h>

GLint Width = 500, Height = 500;

GLint xc = 0, yc = 0, zc = 0;
GLfloat tmp,tmp1 = 0;
GLfloat mat_specular1[]={0.3, 0.3, 0.3, 1.0};
GLfloat mat_defuse1[]={0.0, 0.7, 0.7, 1.0};
GLfloat mat_shininess1[]={10.0};
//GLfloat mat_specular2[]={1.0, 1.0, 1.0, 1.0};
GLfloat mat_defuse2[]={0.5, 0.2, 0.2, 1.0};
GLfloat mat_shininess2[]={128.0};
//GLfloat mat_specular3[]={1.0, 1.0, 1.0, 1.0};
GLfloat mat_defuse3[]={1.0, 0.2, 0.2, 1.0};
GLfloat mat_shininess3[]={128.0};

float par1Angle=0;
float par2Angle=0;
int camXAngle=0;
int camYAngle=0;
float camMove=0.0;
float camMax=-0.4;
float camMin=20.0;
float scale=1;

float speed = 0.5;

void init(void)
{

  GLfloat light_position[]={6.0, -2.0, 10.0, 0.0};
  GLfloat white_light[]={1.0, 1.0, 1.0, 1.0};
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void InitCam(){
  glRotatef((GLfloat)camYAngle,1.0,0.0,0.0);
  glRotatef((GLfloat)camXAngle,0.0,1.0,0.0);
}

void display(void)
{
  
  glPushMatrix();
  
  glScalef(scale,scale,scale);
  glEnable(GL_NORMALIZE);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse1);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
  InitCam();
  glutSolidSphere(0.4,100,100);
  glPushMatrix();
  
  //glRotatef((GLfloat)tmp, 0.0, 0.0, 1.0);
  glTranslatef(0.4, 0.0, 0.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse2);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
  glutSolidCone(0.1, 0.3, 4, 1);
  glPopMatrix();
  
  
  glPushMatrix();
  //glRotatef((GLfloat)tmp1, 1.0, 0.0, 0.0);
  glTranslatef(0.0, 0.4, 0.0);
  glRotatef(90.0, -1.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_defuse3);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess3);
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
  //gluLookAt(0.5, -0.4, 1.0, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



void idle() {
  tmp += speed;
  tmp1 -= speed;
  par1Angle+=0.5;
  par2Angle-=0.3;
  if(par1Angle>=360.0){par1Angle-=360.0;}
  if(par2Angle>=360.0){par2Angle-=360.0;}
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
    
    case '+':
      if(scale<3){
      scale+=0.2;
      }
    break;
    
    case '-':
      if(scale>0.2){
      scale-=0.1;
      }
    break;
    
    default:
    break;
  }
  glutPostRedisplay();
}

void Keys(int key,int x, int y)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      camYAngle+=5;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_RIGHT:
      camXAngle-=5.0;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_LEFT:
      camXAngle+=5.0;
      glutPostRedisplay();
    break;
    
    case GLUT_KEY_DOWN:
      camYAngle-=5.0;
      glutPostRedisplay();
    break;
    
    default:
    break;
  }
}


int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Drawing a Little Blue Sphere with cones");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Keys);
  glutMainLoop();
  return 0;
}
