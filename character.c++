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
#define ROTATE 3

// Character orientation/direction
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define MAP_CELL_WIDTH 25

class Character
{
private:
    float x, y, vx, vy, v_rotation;
    float status;
    long time_remaining, time_remaining_rotation;
    int id;
    float rotation;
    float orientation;
    float colors[3] = {0, 0, 1};
    float currentDegree;

    float dest_x, dest_y, dest_orientation;

    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void setOrientation(float orientation) {
        this->orientation = orientation;
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

    void init(int _id, float x, float y, float orientation)
    {
        id = _id;
        status = QUIET;
        setPosition(x, y);
        //setOrientation(orientation);
        //currentDegree = getDegree(orientation);
        //rotation = 90;

        this->orientation = DOWN;
        this->currentDegree = -90;
    }

    void display() {
        int size = 25;

        glPushMatrix();
        glTranslatef(x * MAP_CELL_WIDTH, y * MAP_CELL_WIDTH, 0);
        glTranslatef(size / 2, size / 2, 0);
        glRotatef(this->currentDegree, 0, 0, 1);
        glTranslatef(-size / 2, -size / 2, 0);
        //drawWheels(size, size, size);
        drawBase(size, size, size, colors);
        drawCavin(size, size, size, colors);
        drawCannon(size, size, size);
        glPopMatrix();
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

    void drawWheels(int size_x, int size_y, int size_z){
        int radius = size_x/6;
        GLUquadricObj *quadratic;

        glPushMatrix();
        glTranslatef(size_x/4, size_y / 6, radius);
        glColor3f(0,0,0);
        quadratic = gluNewQuadric();
        gluSphere(quadratic,radius,32,32);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3*size_x/4, size_y / 6, radius);
        glColor3f(0,0,0);
        quadratic = gluNewQuadric();
        gluSphere(quadratic,radius,32,32);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(size_x/4, 5 * size_y / 6, radius);
        glColor3f(0,0,0);
        quadratic = gluNewQuadric();
        gluSphere(quadratic,radius,32,32);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3*size_x/4,5 * size_y / 6, radius);
        glColor3f(0,0,0);
        quadratic = gluNewQuadric();
        gluSphere(quadratic,radius,32,32);
        glEnd();
        glPopMatrix();
    }

    /*void displayOld()
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
    }*/

    int getDegree(int value) {
        int degree = 0;
        switch (value) {
            case UP:
                degree = 90;
                break;
            case DOWN:
                degree = 270;
                break;
            case LEFT:
                degree = 180;
                break;
            case RIGHT:
                degree = 0;
                break;
        }
        return degree;
    }

    void integrate(long t)
    {
        if (status == ROTATE && t < this->time_remaining_rotation) {
            currentDegree = currentDegree + v_rotation * t;
            time_remaining_rotation -= t;
        }
        else if (status == ROTATE && t >= this->time_remaining_rotation) {
            currentDegree = getDegree(dest_orientation);
            orientation = dest_orientation;
            status = MOVE;
            //this->time_remaining = this->time_remaining * 2;
        }
        else if (status == MOVE && t < this->time_remaining)
        {   
            // modifying the position components (x, y)
            x = x + vx * t;
            y = y + vy * t;
            time_remaining -= t;
        }
        else if (status == MOVE && t >= this->time_remaining)
        {
            x = dest_x;
            y = dest_y;
            status = QUIET;
        }
    }

    void init_movement(float destination_x, float destination_y, float dest_orientation, float duration)
    { 
        // MOVEMENT
        vx = (destination_x - x) / duration;
        vy = (destination_y - y) / duration;
        status = MOVE;
        this->time_remaining = duration;

        this->dest_x = destination_x;
        this->dest_y = destination_y;

        // ROTATION
        if (orientation != dest_orientation) {
            
            int dest_degree = getDegree(dest_orientation);
            int src_degree = getDegree(orientation);

            /*int diff = abs(dest_degree - src_degree) % 180;

            if (dest_degree > src_degree) {
                
            }

            v_rotation = diff / duration;*/

            v_rotation = (dest_degree - src_degree) / duration;
            status = ROTATE;
            this->time_remaining_rotation = duration;

            this->dest_orientation = dest_orientation;

            this->currentDegree = getDegree(orientation);
            /*switch ((int) dest_orientation) {
                case UP:
                    orientation = 90;
                    break;
                case DOWN:
                    orientation = 270;
                    break;
                case LEFT:
                    orientation = 180;
                    break;
                case RIGHT:
                    orientation = 0;
                    break;
            };*/
        }
    }
};