/* OpenGL texture info */

typedef struct
{
  GLsizei width;
  GLsizei height;

  GLenum format;
  GLint	internalFormat;
  GLuint id;

  GLubyte *texels;

} gl_texture_t;

gl_texture_t *ReadBMPFile (const char *filename);
