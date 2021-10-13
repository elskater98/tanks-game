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
    }

    void display()
    {
        (id == 0) ? glColor3f(255, 0, 240) : glColor3f(255, 255, 0);

        // HEAD
        glBegin(GL_QUADS); // ROOF
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH);
        glEnd();

        /*glBegin(GL_QUADS); // FLOOR
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH / 2);
        glEnd();*/

        //RIGHT
        /*glBegin(GL_QUADS);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glEnd();

        glBegin(GL_QUADS); // FRONT
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glEnd();

        glBegin(GL_QUADS); // LEFT
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH), MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        glEnd();

        glBegin(GL_QUADS); // BACK
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH / 2);
        glVertex3i(x * (MAP_CELL_WIDTH), y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        glVertex3i(x * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, y * (MAP_CELL_WIDTH) + MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        glEnd();*/

        (id != 0) ? glColor3f(255, 0, 240) : glColor3f(255, 255, 0);
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