// Libraries
#include <GL/glut.h>
#include <iostream>

// Own Libraries

#include "map.c++"
#include "character.c++"

// namespace
using namespace std;

// Global variables
Map map = Map();
Character player = Character();
Character enemy = Character();

int cell_width = 10;
int keyflag=0;
int input_width;
int input_height;
long last_t=0;
int player_speed = 10;

void displaySquare(int R, int G, int B, int x, int y){
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
    glVertex2i(x * (cell_width), y * (cell_width)); // top left
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width)); // top right 
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
    glVertex2i(x * (cell_width), y * (cell_width) + cell_width); // bottom left
    glEnd();
}

void displayWall(int x, int y) {
    displaySquare(0.0,0,1,x,y);
}

void displayCorridor(int x, int y) {
    displaySquare(0.0,0.0,0.0,x,y);
}

void displayInitialPlayer(int x,int y){
    displaySquare(0,100,0,x,y);
}

void displayInitialEnemy(int x, int y){
    displaySquare(139,0,0,x,y);

}

void showMap(){        
    for (int x = 0; x < map.width; x++) {
		for (int y = 0; y < map.height; y++) {
			if (map.array2D[map.getPosition(x,y)] == map.getWallSymbol()) {
                displayWall(x, y);
			}
			else if (map.array2D[map.getPosition(x,y)] == map.getCorridorSymbol()) {
                displayCorridor(x, y);
            }

            if(x==1 && y==map.height-2)
            displayInitialPlayer(x,y);

            if(x==map.width-2 && y==1)
            displayInitialEnemy(x,y);

		}
	}
}

void display() {

 	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	showMap();
    player.display();
    enemy.display();

	glutSwapBuffers();
}

void askDimensions() {
    // Ask map dimensions
    cout << "[Instructions]: Width must be an ODD and geather than height; Height must be EVEN number.\n";
    
    cout << "Enter width: ";
    cin >> input_width;

    cout << "Enter height: ";
    cin >> input_height;

    cout << "[INFO] Generating " << input_width << "x" << input_height;
}

void keyboard(unsigned char c,int x,int y)
{
    switch (c){
        case 'w':
            player.init_movement(player.getX(),player.getY()+1,player_speed);
            break;
        case 's':
            player.init_movement(player.getX(),player.getY()-1,player_speed);
            break;
        case 'a':
            player.init_movement(player.getX()-1,player.getY(),player_speed);
            break;
        case 'd':
            player.init_movement(player.getX()+1,player.getY(),player_speed);
            break;
        default:
            break;
    }


    glutPostRedisplay();
};

void idle(){
    long t;

    t=glutGet(GLUT_ELAPSED_TIME); 

    if(last_t==0){
        last_t=t;
    }
    else{
        player.integrate(t-last_t);
        last_t=t;
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    askDimensions();

    srand(time(NULL)); // Set Seed to geneate random numbers
    map.create(input_width, input_height); // create map
    map.print();

    // Create Player
    player.init(0,1, map.height - 2 );

    // Create Enemy
    enemy.init(1,map.width-2,1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Game ~");

    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,(cell_width * map.width)-1,0,(cell_width * map.height)-1);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    exit(0);
}