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

class Character {
    public:
        void init(int id, float x, float y) {
            this->id = id;
            this->status = QUIET;
            setPosition(x, y);
        }

        float getX() {
            return this->x;
        }

        float getY() {
            return this->y;
        }

        float getStatus() {
            return this->status;
        }

        void integrate(long t) {
            if (status == MOVE && t < time_remaining) {
                x = x + vx * t;
                y = y + vy * t;
                time_remaining -= t;
            }
            else if (status == MOVE && t >= time_remaining) {
                x = dest_x;
                y = dest_y;
                status = QUIET;
            }
        }

        void init_movement(float destination_x, float destination_y, float duration) {
            vx = (destination_x - x) / duration;
            vy = (destination_y - y) / duration;
            status = MOVE;
            time_remaining = duration;

            dest_x = destination_x;
            dest_y = destination_y;
        }

        void display() {
            (id == 0) ? glColor3f(1, 0, 1) : glColor3f(1, 0, 0);

            glPushMatrix();
            glRotatef(-90.0, 0.0, 0.0, 1.0);
            glTranslatef(x, y, 0);

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

    private:
        float x, y; // position (x, y)
        float vx, vy; // velocity vector
        float dest_x, dest_y; // destination point (dest_x, dest_y)
        long time_remaining; // time movement control 
        float status;
        int id; // player or enemy?
        float rotation = 0.0;

        void setPosition(float x, float y) {
            this->x = x;
            this->y = y;
        }
};