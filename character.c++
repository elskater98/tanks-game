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
    // Private properties
    float x, y, vx, vy, v_angular;
    float status;
    long time_remaining, time_remaining_rotation;
    int id; // 0= Player ; 1 = Enemy
    float rotation;
    float orientation;
    float colors[3]; // RGB
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
        // Create Character
        id = _id;
        status = QUIET; // initial state for all characters

        // colors to differentiate among characters
        this->colors[0] = r;
        this->colors[1] = g;
        this->colors[2] = b;

        setPosition(x, y);
        
        // initial orientation & degree
        this->orientation = RIGHT;
        this->currentDegree = getDegree(this->orientation); //0
    }

    /**
    * Display method
    * draws and translates the character onto its position & orientation to the map
    */
    void display()
    {
        glPushMatrix();

        // Positioning on the map
        glTranslatef(x * MAP_CELL_WIDTH, y * MAP_CELL_WIDTH, 0);

        /**
        * Rotation on three steps
        *   - advance the character
        *   - rotate
        *   - back the character
        */
        glTranslatef(MAP_CELL_WIDTH / 2, MAP_CELL_WIDTH / 2, 0);
        glRotatef(this->currentDegree, 0, 0, 1);
        glTranslatef(-MAP_CELL_WIDTH / 2, -MAP_CELL_WIDTH / 2, 0);

        // Drawing
        drawBase(MAP_CELL_WIDTH); // each element based on the CELL_WIDTH
        drawCavin(MAP_CELL_WIDTH); // passing the parameter by value in case we wish drawing an element based on other sizes
        drawCannon(MAP_CELL_WIDTH);

        // Common light configuration for the two spotlights (player & enemy)
        GLint spot_position[4] = {(int) x, (int) y, MAP_CELL_WIDTH, 1};
        GLfloat spot_color[4] = {0.8, 0.8, 0.8, 1};
        GLfloat diffuseLight[4] = {0.1, 0.1, 0.1, 1};/*{0.8f, 0.8f, 0.8f, 1.0f};*/
        GLfloat specularLight[4] = {0.5f, 0.5f, 0.5f, 1.0f};

        // Spotlight (player)
        if (this->id == 0)
        {
            glLightfv(GL_LIGHT1, GL_AMBIENT, spot_color);
            glLightiv(GL_LIGHT1, GL_POSITION, spot_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
            glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 32.0f);
            glEnable(GL_LIGHT1);
        }
        else {
            // Spotlight (enemy)
            // using a different GLenum light
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

    void drawBase(float cell_width)
    {
        //Roof // good
        glColor3f(this->colors[0], this->colors[1], this->colors[2]); // getting the colors from the initial configuration
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, cell_width / 2);                  // left-down
        glVertex3f(7 * cell_width / 8, cell_width / 8, cell_width / 2);     // right-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, cell_width / 2); // right-up
        glVertex3f(0, 7 * cell_width / 8, cell_width / 2);              // left-up
        glEnd();

        //Base
        /*glColor3f(this->colors[0], this->colors[1], this->colors[2]); // getting the colors from the initial configuration
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, 0);                  // left-down
        glVertex3f(7 * cell_width / 8, cell_width / 8, 0);              // right-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, 0);     // right-up 
        glVertex3f(0, 7 * cell_width / 8, 0); // left-up
        glEnd();*/

        //Left
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, 0); // left-down
        glVertex3f(7 * cell_width / 8, cell_width / 8, 0); // right-down
        glVertex3f(7 * cell_width / 8, cell_width / 8, cell_width / 2); // right-up
        glVertex3f(0, cell_width / 8, cell_width / 2);              // left-up
        glEnd();

        //Right
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, 7 * cell_width / 8, 0); // left-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, 0); // right-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, cell_width / 2); // right-up
        glVertex3f(0, 7 * cell_width / 8, cell_width / 2); // left-up
        glEnd();

        //Front
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(7 * cell_width / 8, cell_width / 8, 0); // left-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, 0); // right-down
        glVertex3f(7 * cell_width / 8, 7 * cell_width / 8, cell_width/2); // right-up
        glVertex3f(7 * cell_width / 8, cell_width / 8, cell_width/2); // left-up
        glEnd();

        //Back
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        glBegin(GL_QUADS);
        glVertex3f(0, 7 * cell_width / 8, 0); // left-down
        glVertex3f(0, cell_width / 8, 0); // right-down
        glVertex3f(0, cell_width / 8, cell_width/2); // right-up
        glVertex3f(0, 7 * cell_width / 8, cell_width/2); // left-up
        glEnd();

        // the base is not necessary to be drawn
        // but in any case, would be the same as the roof but nulling to zero the z component
    }

    void drawCavin(int cell_width)
    {
        // Roof
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        //glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, cell_width); // left-down
        glVertex3f(2 * cell_width / 3, cell_width / 8, cell_width); // right-down
        glVertex3f(2 * cell_width / 3, 7 * cell_width / 8, cell_width); // right-up
        glVertex3f(0, 7 * cell_width / 8, cell_width); // left-up
        glEnd();

        // Left
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        //glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, cell_width/2); // left-down
        glVertex3f(2 * cell_width / 3, cell_width / 8, cell_width/2); // right-down
        glVertex3f(2 * cell_width / 3, cell_width / 8, cell_width); // right-up
        glVertex3f(0, cell_width / 8, cell_width); // left-up
        glEnd();

        // Right
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        //glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(0, 7 * cell_width / 8, cell_width/2); // left-down
        glVertex3f(2 * cell_width / 3, 7 * cell_width / 8, cell_width/2); // right-down
        glVertex3f(2 * cell_width / 3, 7 * cell_width / 8, cell_width); // right-up
        glVertex3f(0, 7 * cell_width / 8, cell_width); // left-up
        glEnd();

        // Front
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        //glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(2 * cell_width / 3, cell_width / 8, cell_width/2); // left-down
        glVertex3f(2 *cell_width / 3, 7 * cell_width / 8, cell_width/2); // right-down
        glVertex3f(2 * cell_width / 3, 7 * cell_width / 8, cell_width); // right-up
        glVertex3f(2 * cell_width / 3, cell_width / 8, cell_width); // left-up
        glEnd();

        // Back
        glColor3f(this->colors[0], this->colors[1], this->colors[2]);
        //glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(0, cell_width / 8, cell_width/2); // left-down
        glVertex3f(0, 7 * cell_width / 8, cell_width/2); // right-down
        glVertex3f(0, 7 * cell_width / 8, cell_width); // right-up
        glVertex3f(0, cell_width / 8, cell_width); // left-up
        glEnd();
    }

    void drawCannon(int cell_width)
    {
        float radius = (cell_width / 12);
        GLUquadricObj *quadratic;
        glPushMatrix();
        glTranslatef(cell_width / 2, cell_width / 2, 2 * cell_width / 3 + (cell_width / 4) / 2);
        glRotatef(90, 0, 1, 0);
        glColor3f(0, 0, 0);
        quadratic = gluNewQuadric();
        gluCylinder(quadratic, radius, radius, 2 * cell_width/ 3, 32, 32);
        glEnd();
        glPopMatrix();
    }

    /**
    * Method which enables us to treat with states but also,
    * with degrees when a translation or a rotation integration is needed
    */
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
            status = MOVE; // after rotation, starts the movement
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
        if (this->orientation != dest_orientation) // must the character rotate to move forward? if so, first rotation, then movement
        {
            int dest_degree = getDegree(dest_orientation); // from states to degrees to integrate
            int currentDegree = getDegree(orientation);

            int diff = dest_degree - currentDegree;

            // positive or negative rotation? 
            if (abs(diff) == 270) // if so, only needed 90 degrees to integrate, but what is the sign?
            {
                if (diff >= 0) {
                    diff = -90;
                }
                else {
                    diff = 90;
                }
            }

            v_angular = diff / duration; // velocity for integration, called angular as usual
            status = ROTATE;

            this->time_remaining_rotation = duration; // same duration
            this->dest_orientation = dest_orientation; // to check when accomplished
        }
    }
};