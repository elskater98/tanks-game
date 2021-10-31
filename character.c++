// Libraries
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <random>
#include <algorithm> // std::random_shuffle

// namespace
using namespace std;

// Character status
#define MOVE 1
#define QUIET 2

#define MAP_CELL_WIDTH 25

class Character
{
private:
    float x, y, vx, vy;
    float status;
    long time_remaining;
    int id;
    float rotation;
    float colors[3] = {0, 0, 1};

    float dest_x, dest_y;

    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

public:
    float getX()
    {
        return this->x;
    }

    float getY()
    {
        return this->y;
    }

    float getStatus()
    {
        return this->status;
    }

    void init(int _id, float x, float y)
    {
        id = _id;
        status = QUIET;
        setPosition(x, y);
        //rotation = 90;
    }

    void display() {
        int size_x = 20;
        int size_y = 20;

        glPushMatrix();
        glTranslatef(x, y, 0);
        glTranslatef(size_x / 2, size_y / 2, 0);
        glTranslatef(-size_x / 2, -size_y / 2, 0);
        glPushMatrix();
        drawBase(20,20,20, colors);
        glPopMatrix();
        glPopMatrix();

        //drawBase(20,20,20, colors);
        //drawCavin();
        //drawCannon();
    }

    void drawBase(int size_x, int size_y, int size_z, float color[3]){

        /*Part de Baix*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, size_y / 6);
        glVertex3f(size_x,  size_y / 6, size_y / 6);
        glVertex3f(size_x,  5 * size_y / 6, size_y / 6);
        glVertex3f(0, 5 * size_y / 6, size_y / 6);
        glEnd();

        /*Part de Dalt*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x, size_y / 6, 2 * size_z / 3 );
        glEnd();

        /*Part Esquerra*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0,  size_y / 6, size_y / 6);
        glVertex3f(0,  size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x,  size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x,  size_y / 6, size_y / 6);
        glEnd();

        /*Part Dreta*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, 5 * size_y / 6, size_y / 6);
        glVertex3f(size_x, 5 * size_y / 6, size_y / 6);
        glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glEnd();

        /*Part Frontal*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(size_x, size_y / 6, size_y / 6);
        glVertex3f(size_x, size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x, 5 * size_y / 6, size_y / 6);
        glEnd();

        /*Part Darrere*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, size_y / 6);
        glVertex3f(0, 5 * size_y / 6, size_y / 6);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);
        glEnd();
    }

    void drawCavin(int size_x, int size_y, int size_z, float color[3]){

        /*Part de Dalt*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, size_z);
        glVertex3f(0, 5 * size_y / 6, size_z);
        glVertex3f(size_x/2, 5 * size_y / 6, size_z);
        glVertex3f(size_x/2, size_y / 6, size_z);
        glEnd();

        /*Part Esquerra*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);
        glVertex3f(0, size_y / 6, size_z);
        glVertex3f(size_x/2, size_y / 6, size_z);
        glVertex3f(size_x/2, size_y / 6, 2 * size_y / 3);
        glEnd();

        /*Part Dreta*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0,  5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x/2, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x/2, 5 * size_y / 6, size_z);
        glVertex3f(0, 5 * size_y / 6, size_z);
        glEnd();

        /*Part Frontal*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(size_x/2, size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x/2, size_y / 6, size_z);
        glVertex3f(size_x/2, 5 * size_y / 6, size_z);
        glVertex3f(size_x/2, 5 * size_y / 6, 2 * size_y / 3);
        glEnd();

        /*Part Darrere*/
        glColor3f(color[0],color[1],color[2]);
        glBegin(GL_QUADS);
        glVertex3f(0,  size_y / 6, 2 * size_y / 3);
        glVertex3f(0,  5 * size_y / 6, 2 * size_y / 3);
        glVertex3f(0,  5 * size_y / 6, size_z);
        glVertex3f(0,  size_y / 6, size_z);
        glEnd();

    }

    void drawCannon(int size_x, int size_y, int size_z){
        float radius = (size_z / 12);
        GLUquadricObj *quadratic;
        glPushMatrix();
        glTranslatef(size_x/2, size_y / 2, 3 * size_z / 4 + (size_z / 4) / 2);
        glRotatef(90, 0, 1, 0);
        glColor3f(0,0,0);
        quadratic = gluNewQuadric();
        gluCylinder(quadratic, radius, radius, size_x/2, 32, 32);
        glEnd();
        glPopMatrix();

    }

    

    void displayOld()
    {
        (id == 0) ? glColor3f(1, 0, 1) : glColor3f(1, 0, 0);

        glPushMatrix();
        glRotatef(90, 0, 0, 1);
        glTranslatef((25-x-2)*MAP_CELL_WIDTH, -25*MAP_CELL_WIDTH, 0); // (x, y, z)

        // HEAD
        glBegin(GL_QUADS); // ROOF
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glEnd();

        glBegin(GL_QUADS); // FLOOR
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glEnd();

        //RIGHT
        glBegin(GL_QUADS);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glEnd();

        glBegin(GL_QUADS); // FRONT
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glEnd();

        glBegin(GL_QUADS); // LEFT
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glEnd();

        glBegin(GL_QUADS); // BACK
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5) * 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH - MAP_CELL_WIDTH / 4);
        glEnd();

        (id == 0) ? glColor3f(0, 0, 1) : glColor3f(1, 0.5, 0);
        // BODY
        glBegin(GL_QUADS); // ROOF
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * MAP_CELL_WIDTH + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * MAP_CELL_WIDTH + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glEnd();

        glBegin(GL_QUADS); // FLOOR
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * MAP_CELL_WIDTH + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * MAP_CELL_WIDTH + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, 0);
        glEnd();

        //RIGHT
        glBegin(GL_QUADS);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glEnd();

        glBegin(GL_QUADS); // FRONT
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glEnd();

        glBegin(GL_QUADS); // LEFT
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), MAP_CELL_WIDTH / 2);
        glEnd();

        glBegin(GL_QUADS); // BACK
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, 0);
        glVertex3i(x * (MAP_CELL_WIDTH) + (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH - (MAP_CELL_WIDTH / 5), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glEnd();
        glPopMatrix();
        glColor4f(1.f, 1.f, 1.f, 1.f);
    }

    void integrate(long t)
    {
        if (status == MOVE && t < time_remaining)
        {
            x = x + vx * t;
            y = y + vy * t;
            time_remaining -= t;
        }
        else if (status == MOVE && t >= time_remaining)
        {
            x = dest_x;
            y = dest_y;
            status = QUIET;
        }
    }

    void init_movement(float destination_x, float destination_y, float duration)
    {
        vx = (destination_x - x) / duration;
        vy = (destination_y - y) / duration;
        status = MOVE;
        time_remaining = duration;

        dest_x = destination_x;
        dest_y = destination_y;
    }
};