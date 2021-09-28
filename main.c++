// Libraries
#include <GL/glut.h>
#include <iostream>

// Own Libraries

#include "map.c++"
#include "pacman.c++"

// namespace
using namespace std;

// Global variables
Map map = Map();
int cell_width = 10;
int keyflag=0;
int input_width = 25;
int input_height = 25;

Pacman player;
int initX;
int initY;

void displayWall(int x, int y) {
    glColor3f(0.0,0.0,1);

    /*glLineWidth(2);

    if (y==0 || map.array2D[map.getPosition(x,y-1)] != map.getWallSymbol()) {
        glBegin(GL_LINES);
            glVertex2f(x * (cell_width) + cell_width, y * (cell_width)); // top right 
            glVertex2f(x * (cell_width), y * (cell_width)); // top left
        glEnd();
    }
    
    if (x == 0 || map.array2D[map.getPosition(x-1,y)] != map.getWallSymbol()) {
        glBegin(GL_LINES);
            glVertex2f(x * (cell_width), y * (cell_width)); // top left
            glVertex2f(x * (cell_width), y * (cell_width) + cell_width); // bottom left
        glEnd();
    }

    if (x == map.width-1 || map.array2D[map.getPosition(x+1,y)] != map.getWallSymbol()) {
        glBegin(GL_LINES);
            glVertex2f(x * (cell_width) + cell_width, y * (cell_width)); // top right
            glVertex2f(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
        glEnd();
    }

    if (y == map.height-1 || map.array2D[map.getPosition(x,y+1)] != map.getWallSymbol()) {
        glBegin(GL_LINES);
            glVertex2f(x * (cell_width), y * (cell_width) + cell_width); // bottom left
            glVertex2f(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
        glEnd();
    }*/

    glBegin(GL_QUADS);
    glVertex2i(x * (cell_width), y * (cell_width)); // top left
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width)); // top right 
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
    glVertex2i(x * (cell_width), y * (cell_width) + cell_width); // bottom left
    glEnd();
}

void displayCorridor(int x, int y) {
    glColor3f(0.0,0.0,0.0);

    glBegin(GL_QUADS);
    glVertex2i(x * (cell_width), y * (cell_width)); // top left
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width)); // top right 
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
    glVertex2i(x * (cell_width), y * (cell_width) + cell_width); // bottom left
    glEnd();
    
}

void showMap(){        
    for (int x = 0; x < map.width; x++) {
		for (int y = 0; y < map.height; y++) {

            /*switch(map.array2D[map.getPosition(x,y)]) {
                case map.getWallSymbol():
                    glColor3f(0.0,0.0,1); // Black
                    break;
                case map.getCorridorSymbol():
                    glColor3f(0.0,0.0,0.0);
                    break;
            }*/

			if (map.array2D[map.getPosition(x,y)] == map.getWallSymbol() /*|| map.array2D[map.getPosition(x,y)] == '1'*/) {
				//glColor3f(0.0,0.0,1); // Black
                displayWall(x, y);
			}
			else if (map.array2D[map.getPosition(x,y)] == map.getCorridorSymbol() /*|| map.array2D[map.getPosition(x,y)] == '0'*/) {
				//glColor3f(255.0,255.0,255.0); // White
                //glColor3f(0.0,0.0,0.0);
                displayCorridor(x, y);
            }
		}
	}
}

void display() {

 	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	showMap();

	glutSwapBuffers();
}

void askDimensions() {
    // Ask map dimensions
    cout << "[Instructions]: Width must be an ODD and geather than height; Height mus be EVEN number.\n";
    
    cout << "Enter width: ";
    cin >> input_width;

    cout << "Enter height: ";
    cin >> input_height;

    cout << "[INFO] Generating " << input_width << "x" << input_height;
}

int main(int argc, char *argv[]) {

    askDimensions();

    srand(time(NULL)); // Set Seed to geneate random numbers
    map.create(input_width, input_height); // create map
    map.print();

    //askStartingPoint();
    //player.set_position((initX * cell_width)-cell_width/2,(initY*cell_width)-cell_width/2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Pacman Game ~");

    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,(cell_width * map.width)-1,0,(cell_width * map.height)-1);

    glutMainLoop();

    exit(0);
}