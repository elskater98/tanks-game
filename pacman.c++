#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

void set_position(int x,int y);
void draw();

class Pacman {

public:

	float x,y;

public:

	Pacman() {}

	void set_position(int x,int y) {
	  this->x = x;
	  this->y = y;
	}

	void draw() {
	  glColor3f(1,1,0); //yellow!
	  glBegin(GL_QUADS);
	  glVertex2i(floor(x)-10,floor(y)-10);
	  glVertex2i(floor(x)+10,floor(y)-10);
	  glVertex2i(floor(x)+10,floor(y)+10);
	  glVertex2i(floor(x)-10,floor(y)+10);
	  glEnd();
	}
};