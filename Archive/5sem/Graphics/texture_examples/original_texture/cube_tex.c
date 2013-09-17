
/* Copyright (c) Mark J. Kilgard, 1997. */

/* gcc cube_tex.c -o cube_tex -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat light_diffuse1[] = {1.0, 1.0, 1.0, 1.0};   /* White diffuse light. */
GLfloat light_position1[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light1 location. */

GLfloat light_diffuse2[] = {1.0, 1.0, 1.0, 1.0};   /* White diffuse light. */
GLfloat light_position2[] = {-1.0, 1.0, -1.0, 0.0}; /* Infinite light2 location. */

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };

GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

static GLuint name[3];

void drawBox(void) {
  int i;

  glEnable(GL_TEXTURE_2D);
  for (i = 0; i < 6; i++) {
    glBindTexture(GL_TEXTURE_2D, name[i/2]);
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glTexCoord2f(0,0); /* glue vertex of texture to vertex of square */ 
    glVertex3fv(&v[faces[i][0]][0]);
    glTexCoord2f(0,1); 
    glVertex3fv(&v[faces[i][1]][0]);
    glTexCoord2f(1,1); 
    glVertex3fv(&v[faces[i][2]][0]);
    glTexCoord2f(1,0); 
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}

void init(void) {
  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1.5;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.5;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1.5;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1.5;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1.5;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1.5;

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
  gluLookAt(7.0, -2, 5.0,  /* eye is at (7,-2,5) */
            0.0, 0.0, 0.0,  /* center is at (0,0,0) */
            0.0, 1.0, 0.0); /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);  /* shift to z=-1 */
  glRotatef(60, 1.0, 0.0, 0.0);  /* rotate 60 degree around x-axe */
  glRotatef(-20, 0.0, 0.0, 1.0); /* rotate -20 degree around z-axe */

  /* Setup the projection model */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 50.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 15.0);
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, a);
  glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/* load texures & set parameters */
void loadtex(){
  GLubyte f1[64][64][4];
  GLubyte f2[64][64][4];
  GLubyte f3[64][64][4];

  objread("textures/cheese", f1, 64, 64); /* texture of cheese */
  objread("textures/wood", f2, 64, 64);   /* texture of wood */
  objread("textures/stone", f3, 64, 64);  /* texture of stone */
  
  glGenTextures(3, name);

  assigntex(f1, &name[0]);
  assigntex(f2, &name[1]);
  assigntex(f3, &name[2]);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("3D lighted cube");
  glutDisplayFunc(display);
  loadtex(); 
  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
