/* gcc tex_square.c bmp_texture.c -o tex_square -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu */

#include <stdlib.h>

/* подключаем библиотеку GLUT */
#include <GL/glut.h>
#include "bmp_texture.h"

/* начальная ширина и высота окна */
GLint Width = 512, Height = 512;

/* размер куба */
const int CubeSize = 200;


/* загрузка текстуры */
GLuint loadBMPTexture (const char *filename){
  gl_texture_t *bmp_tex = NULL;
  GLuint tex_id = 0;

  bmp_tex = ReadBMPFile (filename);

  if (bmp_tex && bmp_tex->texels)
    {
      /* generate texture */
      glGenTextures (1, &bmp_tex->id);
      glBindTexture (GL_TEXTURE_2D, bmp_tex->id);

      /* setup some parameters for texture filters and mipmapping */
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      /*
      glTexImage2D (GL_TEXTURE_2D, 0, bmp_tex->internalFormat,
		    bmp_tex->width, bmp_tex->height, 0, bmp_tex->format,
		    GL_UNSIGNED_BYTE, bmp_tex->texels);
      */

      gluBuild2DMipmaps (GL_TEXTURE_2D, bmp_tex->internalFormat,
			 bmp_tex->width, bmp_tex->height,
			 bmp_tex->format, GL_UNSIGNED_BYTE, bmp_tex->texels);

      tex_id = bmp_tex->id;

      /* OpenGL has its own copy of texture data */
      free (bmp_tex->texels);
      free (bmp_tex);
    }

  return tex_id;
}

/* эта функция управляет всем выводом на экран */
void Display(void)
{
    
    GLuint texId;
    /* load png texture */
    if ( !(texId = loadBMPTexture("textures/texture2.bmp"))){
      exit (-1);
    }

    glEnable (GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, texId);
    
    int left, right, top, bottom;

    left  = (Width - CubeSize) / 2;
    right = left + CubeSize;
    bottom = (Height - CubeSize) / 2;
    top = bottom + CubeSize;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glColor3ub(255,0,0);
    glBegin(GL_QUADS);
      glTexCoord2f (0.0, 0.0);
      glVertex2f(left,bottom);

      glTexCoord2f (1.0, 0.0);
      glVertex2f(right,bottom);
      
      glTexCoord2f (1.0, 1.0);
      glVertex2f(right,top);

      glTexCoord2f (0.0, 1.0);
      glVertex2f(left,top);
    glEnd();

    glFinish();
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
    Width = w;
    Height = h;

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, w, h);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);
}


/* Главный цикл приложения */
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Texture square example");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
