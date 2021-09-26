// Libraries
#include <GL/glut.h>
#include <iostream>

// Own Libraries

#include "map.c++"

// namespace
using namespace std;

// Global variables
Map map = Map();
int cell_width = 40;
int keyflag=0;

void showMap(){
    glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
            
    for (int x = 0; x < map.width; x++) {
		for (int y = 0; y < map.heigth; y++) {
			if (map.array2D[map.getPosition(x,y)] == '#' || map.array2D[map.getPosition(x,y)] == '1') {
				glColor3f(0.0,0.0,0.0); // Black

			}
			else if (map.array2D[map.getPosition(x,y)] == ' ' || map.array2D[map.getPosition(x,y)] == '0')
				glColor3f(255.0,255.0,255.0); // White

			glBegin(GL_QUADS);
				glVertex2i(x * (cell_width), y * (cell_width)); // top left
				glVertex2i(x * (cell_width) + cell_width, y * (cell_width)); // top right 
				glVertex2i(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
				glVertex2i(x * (cell_width), y * (cell_width) + cell_width); // bottom left
			glEnd();
		}
	}
    glutSwapBuffers();
}

void display() {

 	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	showMap();

	glutSwapBuffers();
}

int main(int argc,char *argv[]) {

    // Ask map dimensions
    int input_width,input_heigth;
    cout << "[Instructions]: Width must be an ODD and geather than height; Height mus be EVEN number.\n";

    cout << "Enter width: ";
    cin >> input_width; 

    cout << "Enter height: ";
    cin >> input_heigth; 

    cout << "[INFO] Generating " << input_width << "x" << input_heigth;

    
    srand(time(NULL)); // Set Seed to geneate random numbers

    // Create Map
    map.create(input_width,input_heigth);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.heigth);
    glutCreateWindow("~Game~");

    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,(cell_width * map.width)-1,0,(cell_width * map.heigth)-1);

    glutMainLoop();

    exit(0);
}