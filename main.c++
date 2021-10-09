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

// Character status
#define MOVE 1
#define QUIET 2

#define PI 3.1416

// Global variables
Map map = Map();
Character player = Character();
Character enemy = Character();

int cell_width = 25;
int keyflag = 0;
int input_width;
int input_height;
long last_t = 0;
int player_speed = 200;
int enemy_speed = 200;

// Observation
int anglealpha = 0;
int anglebeta = 25;

float zoomLevel = 0.5f;
float cameraX;
float cameraY;

void displaySquare(int R, int G, int B, int x, int y)
{

    /*
        V4--------V3  |
        |   /     |  /
        |  /      | /
        | /       |/
        V1--------V2
    */

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);                           // V1
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);              // V2
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width); // V3
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);              // V4

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glEnd();

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glEnd();

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glEnd();

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glEnd();

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glEnd();
}

void displayWall(int x, int y)
{
    displaySquare(0.0, 0, 1, x, y);
}

void displayCorridor(int x, int y)
{
    displaySquare(0.0, 0.0, 0.0, x, y);
}

void displayInitialPlayer(int x, int y)
{
    displaySquare(0, 100, 0, x, y);
}

void displayInitialEnemy(int x, int y)
{
    displaySquare(139, 0, 0, x, y);
}

void showMap()
{
    for (int x = 0; x < map.width; x++)
    {
        for (int y = 0; y < map.height; y++)
        {
            if (map.array2D[map.getPosition(x, y)] == map.getWallSymbol())
            {
                displayWall(x, y);
            }
            else if (map.array2D[map.getPosition(x, y)] == map.getCorridorSymbol())
            {
                displayCorridor(x, y);
            }

            // Player
            if (x == 1 && y == map.height - 2)
            {
                displayInitialPlayer(x, y);
            }

            // Enemy
            if (x == map.width - 2 && y == 1)
            {
                displayInitialEnemy(x, y);
            }
        }
    }
}

bool isWall(int x, int y)
{
    return map.array2D[map.getPosition(x, y)] == map.getWallSymbol();
}

bool charactersEnemyCollision(int x, int y)
{
    return x == enemy.getX() && y == enemy.getY();
}

bool charactersPlayerCollision(int x, int y)
{
    return x == player.getX() && y == player.getY();
}

void PositionObserver(float alpha, float beta, int radi)
{
    float x, y, z;
    float upx, upy, upz;
    float modul;

    x = (float)radi * cos(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);
    y = (float)radi * sin(beta * 2 * PI / 360.0);
    z = (float)radi * sin(alpha * 2 * PI / 360.0) * cos(beta * 2 * PI / 360.0);

    if (beta > 0)
    {
        upx = -x;
        upz = -z;
        upy = (x * x + z * z) / y;
    }
    else if (beta == 0)
    {
        upx = 0;
        upy = 1;
        upz = 0;
    }
    else
    {
        upx = x;
        upz = z;
        upy = -(x * x + z * z) / y;
    }

    modul = sqrt(upx * upx + upy * upy + upz * upz);

    upx = upx / modul;
    upy = upy / modul;
    upz = upz / modul;

    gluLookAt(x, y, z, 0.0, 0.0, 0.0, upx, upy, upz);
}

void display()
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PositionObserver(anglealpha, anglebeta, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((-cameraX * 0.6) - zoomLevel * 2,
            (cameraX * 0.6) + zoomLevel * 2,
            (-cameraY * 0.6) - zoomLevel * 2,
            (cameraY * 0.6) + zoomLevel * 2,
            5, 2000);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    showMap();
    player.display();
    enemy.display();

    glutSwapBuffers();
}

void askDimensions()
{
    // Ask map dimensions
    cout << "[Instructions]: Width and height must be ODD.\n";

    cout << "Enter width: ";
    cin >> input_width;

    cout << "Enter height: ";
    cin >> input_height;

    cout << "[INFO] Generating " << input_width << "x" << input_height;
}

void zoomFunc(int direction)
{

    if (direction == 1)
    {
        cameraX += (cameraX - cell_width * map.width) * 0.5f;
        cameraY += (cameraY - cell_width * map.height) * 0.5f;
        zoomLevel += 2.5f;
    }
    else if (direction == 2)
    {
        cameraX -= (cameraX - cell_width * map.width) * 0.5f;
        cameraY -= (cameraY - cell_width * map.height) * 0.5f;
        zoomLevel -= 2.5f;
    }
    else if (direction == 3)
    {
        cameraX = (cell_width * map.width);
        cameraY = (cell_width * map.height);
        zoomLevel = 1.5f;
    }
}

void keyboard(unsigned char c, int x, int y)
{

    switch (c)
    {
    case 'w':
        if (player.getStatus() == QUIET && !isWall(player.getX(), player.getY() + 1) && !charactersEnemyCollision(player.getX(), player.getY() + 1))
        {
            player.init_movement(player.getX(), player.getY() + 1, player_speed);
        }
        break;
    case 's':
        if (player.getStatus() == QUIET && !isWall(player.getX(), player.getY() - 1) && !charactersEnemyCollision(player.getX(), player.getY() - 1))
        {
            player.init_movement(player.getX(), player.getY() - 1, player_speed);
        }
        break;
    case 'a':
        if (player.getStatus() == QUIET && !isWall(player.getX() - 1, player.getY()) && !charactersEnemyCollision(player.getX() - 1, player.getY()))
        {
            player.init_movement(player.getX() - 1, player.getY(), player_speed);
        }
        break;
    case 'd':
        if (player.getStatus() == QUIET && !isWall(player.getX() + 1, player.getY()) && !charactersEnemyCollision(player.getX() + 1, player.getY()))
        {
            player.init_movement(player.getX() + 1, player.getY(), player_speed);
        }
        break;
    case 'r':
        map.create(input_width, input_height);
        player.init(0, 1, map.height - 2);
        enemy.init(1, map.width - 2, 1);
        break;
    case 'i':
        if (anglebeta <= (90 - 4))
        {
            anglebeta = (anglebeta + 3);
        }
        break;
    case 'k':
        if (anglebeta >= (-90 + 4))
        {
            anglebeta = anglebeta - 3;
        }
        break;
    case 'j':
        anglealpha = (anglealpha + 3) % 360;
        break;
    case 'l':
        anglealpha = (anglealpha - 3 + 360) % 360;
        break;
    case '-':
        zoomFunc(1);
        break;
    case '+':
        zoomFunc(2);
        break;
    case 'z':
        zoomFunc(3);
        break;
    default:
        break;
    }

    glutPostRedisplay();
};

void idle()
{
    long t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0)
    {
        last_t = t;
    }
    else
    {
        player.integrate(t - last_t);
        enemy.integrate(t - last_t);
        last_t = t;
    }

    glutPostRedisplay();
}

void moveEnemy()
{

    //float weights[4] = {0.4,0.1,0.1,0.4};

    while (true)
    { // Player Initial Position

        /*float order[4];

        for (int i = 0; i < 4; i++){
            order[i] = pow(rand() % 10, 1 / weights[i]);
        }

        sort(weights, weights + sizeof(weights) / sizeof(weights[0]));*/

        float d = rand() % 10;
        int direction[4] = {UP, RIGHT, LEFT, DOWN};
        ;

        if (d < 5)
        {
            direction[1] = UP;
            direction[3] = LEFT;
        }

        std::random_shuffle(direction, direction + (sizeof(direction) / sizeof(direction[0])));

        for (int i = 0; i < 4; i++)
        {

            int aux = 0;
            if (enemy.getStatus() == QUIET)
            {
                switch (direction[i])
                {
                case UP:
                    if (!isWall(enemy.getX(), enemy.getY() + 1) && !charactersPlayerCollision(enemy.getX(), enemy.getY() + 1))
                    {
                        enemy.init_movement(enemy.getX(), enemy.getY() + 1, enemy_speed);
                    }
                    break;
                case DOWN:
                    if (!isWall(enemy.getX(), enemy.getY() - 1) && !charactersPlayerCollision(enemy.getX(), enemy.getY() - 1))
                    {
                        enemy.init_movement(enemy.getX(), enemy.getY() - 1, enemy_speed);
                    }
                    break;
                case LEFT:
                    if (!isWall(enemy.getX() - 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() - 1, enemy.getY()))
                    {
                        enemy.init_movement(enemy.getX() - 1, enemy.getY(), enemy_speed);
                    }
                    break;
                case RIGHT:
                    if (!isWall(enemy.getX() + 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() + 1, enemy.getY()))
                    {
                        enemy.init_movement(enemy.getX() + 1, enemy.getY(), enemy_speed);
                    }
                    break;
                }
            }

            usleep(200000);
            // END GAME https://www.youtube.com/watch?v=dE1P4zDhhqw
            if ((enemy.getX() == 1 && enemy.getY() == map.height - 2) || (player.getX() == map.width - 2 && player.getY() == 1))
            {
                exit(0);
            }
        }
    }
}

int main(int argc, char *argv[])
{

    askDimensions();

    srand(time(NULL));                     // Set Seed to geneate random numbers
    map.create(input_width, input_height); // create map
    cameraX = (cell_width * map.width);
    cameraY = (cell_width * map.height);
    map.print();

    // Create Player
    player.init(0, 1, map.height - 2);

    // Create Enemy
    enemy.init(1, map.width - 2, 1);
    thread t1(moveEnemy);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Game ~");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    exit(0);
}