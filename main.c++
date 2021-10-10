// Libraries
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <math.h>
#include <chrono>
#include <ctime>
#include <jpeglib.h>

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
int anglealpha = 165;
int anglebeta = 0;

float zoomLevel = 0.25f;
float cameraX;
float cameraY;

auto start = std::chrono::system_clock::now();
auto maxTimeLeft = 120.0; // seconds

void displayWall(int x, int y)
{
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);                           // V1
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);              // V2
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width); // V3
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);              // V4

    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glEnd();
}

void displayCorridor(int x, int y)
{

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);                           // V1
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);              // V2
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width); // V3
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);              // V4

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glEnd();
}

void displayInitialPlayer(int x, int y)
{

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);                           // V1
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);              // V2
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width); // V3
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);              // V4

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glEnd();

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glEnd();

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glEnd();

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glEnd();

    glColor3f(0, 100, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glEnd();
}

void displayInitialEnemy(int x, int y)
{

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);                           // V1
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);              // V2
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width); // V3
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);              // V4

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glEnd();

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glEnd();

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), 0);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glEnd();

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width), 0);
    glVertex3i(x * (cell_width), y * (cell_width), cell_width);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glEnd();

    glColor3f(139, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, 0);
    glVertex3i(x * (cell_width), y * (cell_width) + cell_width, cell_width);
    glVertex3i(x * (cell_width) + cell_width, y * (cell_width) + cell_width, cell_width);
    glEnd();
}

void printTimeLeft()
{
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    // Time Left Exceeded
    if (maxTimeLeft - elapsed_seconds.count() < 0)
    {
        exit(0);
    }

    glColor3f(0.0, 255, 0.0);
    //glTranslatef(cell_width, cell_width,cell_width);

    std::string text = "Time: Left " + std::to_string(maxTimeLeft - elapsed_seconds.count());

    for (int i = 0; i < text.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
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

    PositionObserver(anglealpha, anglebeta, cell_width / 2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho((-cameraX * 0.6) - zoomLevel,
            (cameraX * 0.6) + zoomLevel,
            (-cameraY * 0.6) - zoomLevel,
            (cameraY * 0.6) + zoomLevel,
            10, 2000);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    showMap();
    player.display();
    enemy.display();

    printTimeLeft();

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

void resetZoom()
{

    cameraX = (cell_width * map.width);
    cameraY = (cell_width * map.height);
    zoomLevel = 0.25f;
}

void zoomIn()
{
    cameraX -= (cameraX - cell_width * map.width) * 0.5f;
    cameraY -= (cameraY - cell_width * map.height) * 0.5f;
    zoomLevel -= 2.5f;
}

void zoomOut()
{

    cameraX += (cameraX - cell_width * map.width) * 0.5f;
    cameraY += (cameraY - cell_width * map.height) * 0.5f;
    zoomLevel += 2.5f;
}

void keyboard(unsigned char c, int x, int y)
{

    switch (c)
    {
    // Player Keys
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

    // Reset Map
    case 'r':
        map.create(input_width, input_height);
        player.init(0, 1, map.height - 2);
        enemy.init(1, map.width - 2, 1);
        start = std::chrono::system_clock::now();
        break;

    // Camera Keys
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
        zoomOut();
        break;
    case '+':
        zoomIn();
        break;
    case 'z':
        resetZoom();
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
    while (true)
    {
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

void readJPEG(char *filename, unsigned char **image, int *width, int *height)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    unsigned char **buffer;
    int i, j;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    if ((infile = fopen(filename, "rb")) == NULL)
    {
        printf("Unable to open file %s\n", filename);
        exit(1);
    }

    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_calc_output_dimensions(&cinfo);
    jpeg_start_decompress(&cinfo);

    *width = cinfo.output_width;
    *height = cinfo.output_height;

    *image = (unsigned char *)malloc(cinfo.output_width * cinfo.output_height * cinfo.output_components);

    buffer = (unsigned char **)malloc(1 * sizeof(unsigned char **));
    buffer[0] = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);

    i = 0;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        for (j = 0; j < cinfo.output_width * cinfo.output_components; j++)
        {
            (*image)[i] = buffer[0][j];
            i++;
        }
    }

    free(buffer);
    jpeg_finish_decompress(&cinfo);
}

void LoadTexture(char *filename, int dim)
{
    unsigned char *buffer;
    unsigned char *buffer2;
    int width, height;
    long i, j;
    long k, h;

    readJPEG(filename, &buffer, &width, &height);

    buffer2 = (unsigned char *)malloc(dim * dim * 3);

    //-- The texture pattern is subsampled so that its dimensions become dim x dim --
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        {
            k = i * height / dim;
            h = j * width / dim;

            buffer2[3 * (i * dim + j)] = buffer[3 * (k * width + h)];
            buffer2[3 * (i * dim + j) + 1] = buffer[3 * (k * width + h) + 1];
            buffer2[3 * (i * dim + j) + 2] = buffer[3 * (k * width + h) + 2];
        }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dim, dim, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer2);

    free(buffer);
    free(buffer2);
}

void loadGameTextures()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    LoadTexture("textures/ice.jpg", 64);

    glBindTexture(GL_TEXTURE_2D, 1);
    LoadTexture("textures/ice.jpg", 64);
}

int main(int argc, char *argv[])
{

    askDimensions();

    srand(time(NULL)); // Set Seed to geneate random numbers

    map.create(input_width, input_height); // create map

    // Init Camera Position
    cameraX = (cell_width * map.width);
    cameraY = (cell_width * map.height);

    map.print();

    // Init Time Left
    start = std::chrono::system_clock::now();

    // Create Player
    player.init(0, 1, map.height - 2);

    // Create Enemy
    enemy.init(1, map.width - 2, 1);
    thread t1(moveEnemy);

    // Set window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Game ~");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    loadGameTextures();

    glutMainLoop();

    exit(0);
}