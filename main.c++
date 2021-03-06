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
#include "material.c++"
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
int input_width;
int input_height;
long last_t = 0;
int player_speed = 200;
int enemy_speed = 200;

// Observation
int anglealpha = 64;
int anglebeta = -15;
float zoom = 0.7f;

auto start = std::chrono::system_clock::now();
float maxTimeLeft = 200.0; // seconds

bool DEBUG = false;

// Global material properties
LightMaterial lightMaterial;

void printTimeLeft()
{

    //https://stackoverflow.com/questions/18847109/displaying-fixed-location-2d-text-in-a-3d-opengl-world-using-glut/21923064
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;

    // Time Left Exceeded
    if (maxTimeLeft - elapsed_seconds.count() < 0) {
        exit(0);
    }

    glColor3f(0.0, 255, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, cell_width * map.width, 0.0, cell_width * map.height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f); //needs to be called before RasterPos
    glRasterPos2i(10, 10);

    std::string text = "Time: Left " + std::to_string(maxTimeLeft - elapsed_seconds.count()) + " s";
    void *font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }

    // https://stackoverflow.com/questions/8956736/glcolor-coloring-all-textures/26526213
    glColor4f(1.f, 1.f, 1.f, 1.f); // unbind the texture
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

    gluLookAt(x, y, z, (map.width * cell_width) / 2, (map.height * cell_width) / 2, cell_width, upx, upy, upz);
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PositionObserver(anglealpha, anglebeta, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-cell_width * map.width * zoom, cell_width * map.width * zoom, -cell_width * map.height * zoom, cell_width * map.height * zoom, 10, 2000);

    glMatrixMode(GL_MODELVIEW);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    // enabling lighting mode
    glEnable(GL_LIGHTING);

    // Ambient light configuration
    GLint position[4] = {0, 0, 0, 0};
    GLfloat color[4] = {0.2f, 0.2f, 0.2f, 1.0f};
 
    glLightiv(GL_LIGHT0, GL_POSITION, position);
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glEnable(GL_LIGHT0);

    // Ambient light configuration by material
    lightMaterial.apply();

    // Display map
    map.display();

    // Display palyer/enemy
    player.display();
    enemy.display();

    glDisable(GL_LIGHTING); // disabling lighting mode

    // Time HUD
    printTimeLeft();

    glutSwapBuffers();
    glutPostRedisplay();
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

void keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
        // Player Keys
        case 'w':
            if (player.getStatus() == QUIET && !isWall(player.getX(), player.getY() + 1) && !charactersEnemyCollision(player.getX(), player.getY() + 1))
            {
                player.init_movement(player.getX(), player.getY() + 1, UP, player_speed);
            }
            break;
        case 's':
            if (player.getStatus() == QUIET && !isWall(player.getX(), player.getY() - 1) && !charactersEnemyCollision(player.getX(), player.getY() - 1))
            {
                player.init_movement(player.getX(), player.getY() - 1, DOWN, player_speed);
            }
            break;
        case 'a':
            if (player.getStatus() == QUIET && !isWall(player.getX() - 1, player.getY()) && !charactersEnemyCollision(player.getX() - 1, player.getY()))
            {
                player.init_movement(player.getX() - 1, player.getY(), LEFT, player_speed);
            }
            break;
        case 'd':
            if (player.getStatus() == QUIET && !isWall(player.getX() + 1, player.getY()) && !charactersEnemyCollision(player.getX() + 1, player.getY()))
            {
                player.init_movement(player.getX() + 1, player.getY(), RIGHT, player_speed);
            }
            break;

        // Reset Map
        case 'r':
            map.create(input_width, input_height, cell_width);
            player.init(0, 1, map.height - 2, RIGHT, 0.0, 0.0, 1.0);
            enemy.init(1, map.width - 2, 1, LEFT, 1.0, 0.0, 1.0);
            start = std::chrono::system_clock::now();
            break;

        // Camera Keys
        case 'i':
            anglebeta = (anglebeta + 3);
            break;
        case 'k':
            anglebeta = anglebeta - 3;
            break;
        case 'j':
            anglealpha = (anglealpha + 3) % 360;
            break;
        case 'l':
            anglealpha = (anglealpha - 3 + 360) % 360;
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
    // Random Algorithm to move enemy to player base
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
                        enemy.init_movement(enemy.getX(), enemy.getY() + 1, UP, enemy_speed);
                    }
                    break;
                case DOWN:
                    if (!isWall(enemy.getX(), enemy.getY() - 1) && !charactersPlayerCollision(enemy.getX(), enemy.getY() - 1))
                    {
                        enemy.init_movement(enemy.getX(), enemy.getY() - 1, DOWN, enemy_speed);
                    }
                    break;
                case LEFT:
                    if (!isWall(enemy.getX() - 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() - 1, enemy.getY()))
                    {
                        enemy.init_movement(enemy.getX() - 1, enemy.getY(), LEFT, enemy_speed);
                    }
                    break;
                case RIGHT:
                    if (!isWall(enemy.getX() + 1, enemy.getY()) && !charactersPlayerCollision(enemy.getX() + 1, enemy.getY()))
                    {
                        enemy.init_movement(enemy.getX() + 1, enemy.getY(), RIGHT, enemy_speed);
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
    // https://github.com/hatsyio/Pacman_CPP
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
    // https://github.com/hatsyio/Pacman_CPP
    unsigned char *buffer, *buffer2;
    int width, height;
    long i, j, k, h;

    readJPEG(filename, &buffer, &width, &height);

    buffer2 = (unsigned char *)malloc(dim * dim * 3);

    //-- The texture pattern is subsampled so that its dimensions become dim x dim --
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            k = i * height / dim;
            h = j * width / dim;

            buffer2[3 * (i * dim + j)] = buffer[3 * (k * width + h)];
            buffer2[3 * (i * dim + j) + 1] = buffer[3 * (k * width + h) + 1];
            buffer2[3 * (i * dim + j) + 2] = buffer[3 * (k * width + h) + 2];
        }
    }

    free(buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dim, dim, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer2);

    free(buffer2);
}

void loadGameTextures()
{
    //wall
    glBindTexture(GL_TEXTURE_2D, 0);
    LoadTexture((char *)"textures/wall.jpg", 64);

    // roof
    glBindTexture(GL_TEXTURE_2D, 1);
    LoadTexture((char *)"textures/roof.jpg", 64);

    // path
    glBindTexture(GL_TEXTURE_2D, 2);
    LoadTexture((char *)"textures/floor.jpg", 64);

    // water
    glBindTexture(GL_TEXTURE_2D, 3);
    LoadTexture((char *)"textures/water.jpg", 64);

    // path
    glBindTexture(GL_TEXTURE_2D, 4);
    LoadTexture((char *)"textures/lava.jpg", 64);
}

int main(int argc, char *argv[])
{
    if (DEBUG)
    {
        input_width = 25;
        input_height = 25;
    }
    else
    {
        askDimensions();
    }

    srand(time(NULL)); // Set Seed to geneate random numbers

    map.create(input_width, input_height, cell_width); // create map
    map.print();

    // Init Time Left
    start = std::chrono::system_clock::now();

    // Create Player
    player.init(0, 1, map.height - 2, DOWN, 0.0, 0.0, 1.0);

    // Create Enemy
    enemy.init(1, map.width - 2, 1, LEFT, 1.0, 0.0, 1.0);
    thread t1(moveEnemy);

    // Set window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(cell_width * map.width, cell_width * map.height);
    glutCreateWindow("~ Game ~");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    // Display
    glutDisplayFunc(display);

    // Keyboard
    glutKeyboardFunc(keyboard);

    // Idle
    glutIdleFunc(idle);

    //Load Textures
    loadGameTextures();

    glutMainLoop();

    exit(0);
}