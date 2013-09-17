#include <GL/glut.h>

GLint Width = 512, Height = 512;

void Display(void) {
  
}

void Reshape(GLint w, GLint h) {
}

void Keyboard(unsigned char key, int x, int y) {
}

void Mouse(int button, int state, int x, int y) {
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(Width, Height);
  glutCreateWindow("Hello!");

  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);

  glutMainLoop();
  return 0;
}
