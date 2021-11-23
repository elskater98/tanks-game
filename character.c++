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
    float x, y, vx, vy, v_angular;
    float status;
    long time_remaining, time_remaining_rotation;
    int id;
    float rotation;
    float orientation;
    float colors[3];
    float currentDegree;
    GLfloat spot_direction[3] = {10, 0, 0};

    float dest_x, dest_y, dest_orientation;

    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void setOrientation(float orientation)
    {
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

    void init(int _id, float x, float y, float orientation, float r, float g, float b)
    {
        id = _id;
        status = QUIET;
        this->colors[0] = r;
        this->colors[1] = g;
        this->colors[2] = b;
        setPosition(x, y);
        this->orientation = RIGHT;
        this->currentDegree = 0;
    }

    void display()
    {
        glPushMatrix();

        // Positioning
        glTranslatef(x * MAP_CELL_WIDTH, y * MAP_CELL_WIDTH, 0);

        // Rotation
        glTranslatef(MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH / 2, 0);
        glRotatef(this->currentDegree, 0, 0, 1);
        glTranslatef(-MAP_CELL_WIDTH / 2, -MAP_CELL_WIDTH / 2, 0);

        // Drawing
        drawBase(MAP_CELL_WIDTH, MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        drawCavin(MAP_CELL_WIDTH, MAP_CELL_WIDTH, MAP_CELL_WIDTH);
        drawCannon(MAP_CELL_WIDTH, MAP_CELL_WIDTH, MAP_CELL_WIDTH);

        // Spotlight (player)
        if (this->id == 0)
        {
            GLint spot_position[4];
            GLfloat spot_color[4];
            GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
            GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};

            spot_position[0] = x;
            spot_position[1] = y;
            spot_position[2] = MAP_CELL_WIDTH;
            spot_position[3] = 1;
            spot_color[0] = 0.8;
            spot_color[1] = 0.8;
            spot_color[2] = 0.8;
            spot_color[3] = 1;
            diffuseLight[0] = 0.1;
            diffuseLight[1] = 0.1;
            diffuseLight[2] = 0.1;
            diffuseLight[3] = 1;
            glLightfv(GL_LIGHT1, GL_AMBIENT, spot_color);
            glLightiv(GL_LIGHT1, GL_POSITION, spot_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
            glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 32.0f);
            glEnable(GL_LIGHT1);
        }
        else
        {
            GLint spot_position[4];
            GLfloat spot_color[4];
            GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
            GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};

            spot_position[0] = x;
            spot_position[1] = y;
            spot_position[2] = MAP_CELL_WIDTH;
            spot_position[3] = 1;
            spot_color[0] = 0.8;
            spot_color[1] = 0.8;
            spot_color[2] = 0.8;
            spot_color[3] = 1;
            diffuseLight[0] = 0.1;
            diffuseLight[1] = 0.1;
            diffuseLight[2] = 0.1;
            diffuseLight[3] = 1;
            glLightfv(GL_LIGHT2, GL_AMBIENT, spot_color);
            glLightiv(GL_LIGHT2, GL_POSITION, spot_position);
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0f);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
            glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
            glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 32.0f);
            glEnable(GL_LIGHT2);
        }

        glPopMatrix();
    }

    void drawBase(int size_x, int size_y, int size_z)
    {

        /*Roof*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);                  // left-down
        glVertex3f(5 * size_x / 6, size_y / 6, 2 * size_z / 3);     // right-down
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);              // left-up
        glVertex3f(5 * size_x / 6, 5 * size_y / 6, 2 * size_z / 3); // right-up
        glEnd();

        /*Left*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 0);                           // left-down
        glVertex3f(0, size_y / 6, 2 * size_z / 3);              // left-up
        glVertex3f(5 * size_x / 6, size_y / 6, 2 * size_z / 3); // right-up
        glVertex3f(5 * size_x / 6, size_y / 6, 0);              // right-down
        glEnd();

        /*Right*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, 5 * size_y / 6, 0);
        glVertex3f(5 * size_x / 6, 5 * size_y / 6, 0);
        glVertex3f(5 * size_x / 6, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glEnd();

        /*Front*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(5 * size_x / 6, size_y / 6, 0);
        glVertex3f(5 * size_x / 6, size_y / 6, 2 * size_z / 3);
        glVertex3f(5 * size_x / 6, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(5 * size_x / 6, 5 * size_y / 6, 0);
        glEnd();

        /*Back*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 0);
        glVertex3f(0, 5 * size_y / 6, 0);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);
        glEnd();
    }

    void drawCavin(int size_x, int size_y, int size_z)
    {
        /*Roof*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, size_z);
        glVertex3f(0, 5 * size_y / 6, size_z);
        glVertex3f(size_x / 2, 5 * size_y / 6, size_z);
        glVertex3f(size_x / 2, size_y / 6, size_z);
        glEnd();

        /*Left*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 2 * size_z / 3);
        glVertex3f(0, size_y / 6, size_z);
        glVertex3f(size_x / 2, size_y / 6, size_z);
        glVertex3f(size_x / 2, size_y / 6, 2 * size_y / 3);
        glEnd();

        /*Right*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x / 2, 5 * size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x / 2, 5 * size_y / 6, size_z);
        glVertex3f(0, 5 * size_y / 6, size_z);
        glEnd();

        /*Front*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(size_x / 2, size_y / 6, 2 * size_z / 3);
        glVertex3f(size_x / 2, size_y / 6, size_z);
        glVertex3f(size_x / 2, 5 * size_y / 6, size_z);
        glVertex3f(size_x / 2, 5 * size_y / 6, 2 * size_y / 3);
        glEnd();

        /*Back*/
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, size_y / 6, 2 * size_y / 3);
        glVertex3f(0, 5 * size_y / 6, 2 * size_y / 3);
        glVertex3f(0, 5 * size_y / 6, size_z);
        glVertex3f(0, size_y / 6, size_z);
        glEnd();
    }

    void drawCannon(int size_x, int size_y, int size_z)
    {
        float radius = (size_z / 12);
        GLUquadricObj *quadratic;
        glPushMatrix();
        glTranslatef(size_x / 2, size_y / 2, 3 * size_z / 4 + (size_z / 4) / 2);
        glRotatef(90, 0, 1, 0);
        glColor3f(0, 0, 0);
        quadratic = gluNewQuadric();
        gluCylinder(quadratic, radius, radius, size_x / 2, 32, 32);
        glEnd();
        glPopMatrix();
    }

    int getDegree(int value)
    {
        int degree = 0;
        switch (value)
        {
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
        if (status == ROTATE && t < this->time_remaining_rotation)
        {
            currentDegree = currentDegree + v_angular * t;
            time_remaining_rotation -= t;
        }
        else if (status == ROTATE && t >= this->time_remaining_rotation)
        {
            currentDegree = getDegree(dest_orientation);
            orientation = dest_orientation;
            status = MOVE;
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
        if (this->orientation != dest_orientation)
        {

            int dest_degree = getDegree(dest_orientation);
            int currentDegree = getDegree(orientation);

            int diff = dest_degree - currentDegree;

            if (abs(diff) == 270)
            {
                if (diff >= 0)
                {
                    diff = -90;
                }
                else
                {
                    diff = 90;
                }
            }

            v_angular = diff / duration;
            status = ROTATE;

            this->time_remaining_rotation = duration;
            this->dest_orientation = dest_orientation;
        }
    }
};