#include <stdlib.h>
#include <GL/glut.h>
GLint Width = 512, Height = 512;



void Display(void)
{

    glClearColor(255, 255, 255, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(0,191,255);
    glutSolidSphere(50,160,160);
    
    
    //~ glShadeModel(GL_SMOOTH);
  //~ glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  //~ glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  //~ glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  //~ glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);
  //~ glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

    
    
    glBegin(GL_LINES);
    glColor3ub(1,1,1);
    glVertex3d(-200,0,-200);
    glVertex3d(-200,-200,-200);
    
    glVertex3d(0,-200,-200);
    glVertex3d(-200,-200,-200);
    
    glVertex3d(-200,-200,0);
    glVertex3d(-200,-200,-200);
 
    glEnd();
    /*
    glBegin(GL_TRIANGLES);
    glColor3ub(1,1,1);
    glVertex3d(0,-200,0);
    glVertex3d(85,-200,0);
    glEnd();
    */
    glFinish();
}


void Reshape(GLint w, GLint h)
{
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width, Width, -Height, Height, -512.0, 512.0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(10.0, 10.0, 25.0,  
              0.0, 0.0, 0.0,  
              0.0, 1.0, 0.0); 
    
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
    glutCreateWindow("!!!!");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
