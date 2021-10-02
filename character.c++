// Libraries
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <random>
#include <algorithm>    // std::random_shuffle

// namespace
using namespace std;

#define MOVE 1
#define STOP 0
#define SPEED 0.25
#define MAP_CELL_WIDTH 10

class Character{
    private:
        float x;
        float y;
        float speed;
        float status;

    public:

        float getX(){
            return this->x;
        }

        float getY(){
            return this->y;
        }

        void setPosition(float x, float y){
            this->x = x;
            this->y = y;
        }

        void initPlayer(float x, float y){
            setPosition(x,y);
            status = STOP;
            speed = SPEED;
        }

        void display(){
            glColor3f(255, 0, 240);
            glBegin(GL_QUADS);

            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4); // top left
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4); // top right 
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4); // bottom right
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4); // bottom left
            glEnd();
        }

};