#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat light_diffuse1[] = {1.0, 1.0, 1.0, 1.0};  
GLfloat light_position1[] = {1.0, 1.0, 1.0, 0.0};  

GLfloat light_diffuse2[] = {1.0, 1.0, 1.0, 1.0};   
GLfloat light_position2[] = {-1.0, 1.0, -1.0, 0.0}; 

static GLuint name[3];

void drawBox(void) {
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(-150.0, 150.0, 0.0);
  glBegin(GL_QUADS);
    glTexCoord2f(0,0); 
    glVertex3f(128, 128,0);
    glTexCoord2f(0,1); 
    glVertex3f(-128,128,0);
    glTexCoord2f(1,1); 
    glVertex3f(-128,-128,0);
    glTexCoord2f(1,0); 
    glVertex3f(128,-128,0);
    glEnd();
    glPopMatrix();
    

    
    glPushMatrix();
    glTranslatef(150.0, 150.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); 
    glVertex3f(128, 128,0);
    glTexCoord2f(0,1); 
    glVertex3f(-128,128,0);
    glTexCoord2f(4,1); 
    glVertex3f(-128,-128,0);
    glTexCoord2f(4,0); 
    glVertex3f(128,-128,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150.0, -150.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); 
    glVertex3f(128, 128,0);
    glTexCoord2f(0,4); 
    glVertex3f(-128,128,0);
    glTexCoord2f(4,4); 
    glVertex3f(-128,-128,0);
    glTexCoord2f(4,0); 
    glVertex3f(128,-128,0);
    glEnd();
    glPopMatrix();

            
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}

void init(void) {

/* Enable two OpenGL lights. */

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 900.0, 
            0.0, 0.0, 0.0, 
            0.0, 1.0, 0.0); 

  /* Setup the projection model */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(50, 1.0, 1.0, 1150.0);
}


/* read texture from file to array */
void objread(char *fname, GLubyte a[64][64][4], int w, int h){
  char s[15];
  int k, i, j;
  FILE *f = fopen(fname, "r");
  if (f == NULL){
    perror(fname);
    exit(1);
  }
 
  for (k = 0; k < h*w ; k++){
    j = k / w;
    i = k % w;
    fgets(s, 15, f);
    a[i][j][0] = (GLubyte)atoi(s);
    fgets(s, 15, f);
    a[i][j][1] = (GLubyte)atoi(s);
    fgets(s, 15, f);
    a[i][j][2] = (GLubyte)atoi(s);
    a[i][j][3] = (GLubyte)255;
  }
  fclose(f);
}

/* set parameters of textures */
void assigntex(GLubyte a[64][64][4], GLuint *n){
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glBindTexture(GL_TEXTURE_2D, *n);
  glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,(0.2, 0.0, 0.25, 0.8));
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, a);
  glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/* load texures & set parameters */
void loadtex(){
  GLubyte f1[64][64][4];

  objread("cheese", f1, 64, 64);
  
  
  glGenTextures(1, name);

  assigntex(f1, &name[0]);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(900, 900);
  glutCreateWindow("Textured_quad");
  glutDisplayFunc(display);
  loadtex(); 
  init();
  glutMainLoop();
  return 0;        
}
