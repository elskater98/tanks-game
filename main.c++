// Libraries
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <math.h>

// Own Libraries
#include "map.c++"
#include "character.c++"

// namespace
using namespace std;

// Defined Variables
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Global variables
Map map = Map();
Character player = Character();
Character enemy = Character();

int cell_width = 10;
int keyflag = 0;
int input_width;
int input_height;
long last_t = 0;
int player_speed = 200;
int enemy_speed = 200;

void displaySquare(int R, int G, int B, int x, int y) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2i(x * (cell_width), y * (cell_width)); // top left
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width)); // top right 
    glVertex2i(x * (cell_width) + cell_width, y * (cell_width) + cell_width); // bottom right
    glVertex2i(x * (cell_width), y * (cell_width) + cell_width); // bottom left
    glEnd();
}

void displayWall(int x, int y) {
    displaySquare(0.0, 0, 1, x, y);
}

void displayCorridor(int x, int y) {
    displaySquare(0.0, 0.0, 0.0, x, y);
}

void displayInitialPlayer(int x,int y) {
    displaySquare(0, 100, 0, x, y);
}

void displayInitialEnemy(int x, int y) {
    displaySquare(139, 0, 0, x, y);

}

void showMap() {        
    for (int x = 0; x < map.width; x++) {
		for (int y = 0; y < map.height; y++) {
			if (map.array2D[map.getPosition(x, y)] == map.getWallSymbol()) {
                displayWall(x, y);
			}
			else if (map.array2D[map.getPosition(x, y)] == map.getCorridorSymbol()) {
                displayCorridor(x, y);
            }

            // Player
            if(x == 1 && y == map.height - 2) {
                displayInitialPlayer(x, y);
            }

            // Enemy
            if(x == map.width - 2 && y == 1) {
                displayInitialEnemy(x, y);
            }
		}
	}
}

bool isWall(int x, int y) {
    return map.array2D[map.getPosition(x, y)] == map.getWallSymbol();
}

bool charactersEnemyCollision(int x, int y) {
    return x == enemy.getX() && y == enemy.getY();
}

bool charactersPlayerCollision(int x, int y) {
    return x == player.getX() && y == player.getY();
}


void display() {
 	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	showMap();
    player.display();
    enemy.display();

	glutSwapBuffers();
}

void askDimensions() {
    // Ask map dimensions
    cout << "[Instructions]: Width and height must be ODD.\n";
    
    cout << "Enter width: ";
    cin >> input_width;

    cout << "Enter height: ";
    cin >> input_height;

    cout << "[INFO] Generating " << input_width << "x" << input_height;
}

void keyboard(unsigned char c, int x, int y) {

    if(player.getStatus() == 2){
        switch (c) {
                case 'w':
                    if (!isWall(player.getX(), player.getY() + 1) && !charactersEnemyCollision(player.getX(), player.getY() + 1)) {
                        player.init_movement(player.getX(), player.getY() + 1, player_speed);
                    }
                    break;
                case 's':
                    if (!isWall(player.getX(), player.getY() - 1) && !charactersEnemyCollision(player.getX(), player.getY() - 1)) {
                        player.init_movement(player.getX(), player.getY() - 1, player_speed);
                    }
                    break;
                case 'a':
                    if (!isWall(player.getX() - 1, player.getY()) && !charactersEnemyCollision(player.getX() - 1, player.getY())) {
                        player.init_movement(player.getX() - 1, player.getY(), player_speed);
                    }
                    break;
                case 'd':
                    if (!isWall(player.getX() + 1, player.getY()) && !charactersEnemyCollision(player.getX() + 1, player.getY())) {
                        player.init_movement(player.getX() + 1, player.getY(), player_speed);
                    }
                default:
                    break;
        }    
    }
    glutPostRedisplay();
};

void idle() {
    long t = glutGet(GLUT_ELAPSED_TIME); 

    if(last_t == 0) {
        last_t = t;
    }
    else {
        player.integrate(t - last_t);
        enemy.integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}

void moveEnemy() {
    
    //float weights[4] = {0.4,0.1,0.1,0.4};

    while(true){ // Player Initial Position
        
        /*float order[4];

        for (int i = 0; i < 4; i++){
            order[i] = pow(rand() % 10, 1 / weights[i]);
        }

        sort(weights, weights + sizeof(weights) / sizeof(weights[0]));*/

        float d = rand() % 10;
        int direction[4]= {UP,RIGHT,LEFT,DOWN};;

        if (d < 5)
        {
             direction[1] = UP;
             direction[3] = LEFT; 
        }

        std::random_shuffle(direction, direction + (sizeof(direction)/sizeof(direction[0])));
        
        for (int i = 0; i < 4; i++) {
                
            int aux = 0;
        if(enemy.getStatus() == 2){
            switch (direction[i]) {
                case UP:
                    if (!isWall(enemy.getX(), enemy.getY() + 1) && !charactersPlayerCollision(enemy.getX(), enemy.getY() + 1)) {
                        enemy.init_movement(enemy.getX(), enemy.getY() + 1, enemy_speed);
                    }
                    break;
                case DOWN:
                    if (!isWall(enemy.getX(), enemy.getY() - 1) && !charactersPlayerCollision(enemy.getX(), enemy.getY() - 1)) {
                        enemy.init_movement(enemy.getX(), enemy.getY() - 1, enemy_speed);
                    }
                    break;
                case LEFT:
                    if (!isWall(enemy.getX() - 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() - 1, enemy.getY())) {
                        enemy.init_movement(enemy.getX() - 1, enemy.getY(), enemy_speed);
                    }
                    break;
                case RIGHT:
                    if (!isWall(enemy.getX() + 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() + 1, enemy.getY())) {
                        enemy.init_movement(enemy.getX() + 1, enemy.getY(), enemy_speed);
                    }
                    break;
            }
        }
            
            usleep(200000);
            // END GAME https://www.youtube.com/watch?v=dE1P4zDhhqw
            if((enemy.getX() == 1 && enemy.getY() == map.height - 2) || (player.getX() == map.width - 2 && player.getY() == 1)) {
                exit(0);
            }
        }
    }
}

int main(int argc, char *argv[]) {

    askDimensions();

    srand(time(NULL)); // Set Seed to geneate random numbers
    map.create(input_width, input_height); // create map
    map.print();

    // Create Player
    player.init(0,1, map.height - 2);

    // Create Enemy
    enemy.init(1, map.width - 2, 1);
    thread t1(moveEnemy);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Game ~");

    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, (cell_width * map.width) - 1, 0, (cell_width * map.height) - 1);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    exit(0);
}