// Libraries
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <random>
#include <algorithm>    // std::random_shuffle

// namespace
using namespace std;

// Character actions
#define MOVE 1
#define QUIET 2

#define MAP_CELL_WIDTH 10

class Character{
    private:
        float x;
        float y;
        float vx;
        float vy;
        float status;
        long time_remaining;
        int id;

        void setPosition(float x, float y){
            this->x = x;
            this->y = y;
        }

    public:

        float getX(){
            return this->x;
        }

        float getY(){
            return this->y;
        }

        float getStatus(){
            return this->status;
        }

        void init(int _id, float x, float y){
            id = _id;
            status = QUIET;
            setPosition(x,y);
        }

        void display(){
            if(id==0){
                glColor3f(255, 0, 240);
            }else{
                glColor3f(255, 255, 0);
            }
            
            glBegin(GL_QUADS);

            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4); // top left
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4); // top right 
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4); // bottom right
            glVertex2i(x * MAP_CELL_WIDTH + MAP_CELL_WIDTH/4, y * MAP_CELL_WIDTH + MAP_CELL_WIDTH - MAP_CELL_WIDTH/4); // bottom left
         
            glEnd();
        }

        void integrate(long t){
            if(status==MOVE && t<time_remaining)
            {
                x = x + vx*t;
                y = y + vy*t;
                time_remaining-=t;
            }
            else if(status==MOVE && t>=time_remaining)
            {
                x = x + vx*time_remaining;
                y = y + vy*time_remaining;
                status=QUIET;
            }
        }

        void init_movement(int destination_x,int destination_y,int duration){
            vx = (destination_x - x)/duration;
            vy = (destination_y - y)/duration;

            status=MOVE;
            time_remaining=duration;
        }

};