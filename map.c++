/*
[Additional Information]
    - Symbol ‘#’ represents a “wall” 
    - Symbol ' ' represents a “corridor”
*/

// Libraries
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>    // std::random_shuffle

// namespace
using namespace std;

// constants
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Map{
    public:
    // class properties
    int width;
    int height;
    char *array2D; //https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

    // initMap
    void create(int _width, int _height){
        width=_width;
        height=_height;
        array2D = new char [(int)width*(int)height];

        initWalls();
        recursiveAlgorithm(1,1);
        avoidEndPath();
        setRoom();
        symmetrization();
    }

    void print(){
        cout << "Rows:"<<  width << " Columns:" << height << "\n\n";
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                cout << array2D[getPosition(i,j)] << " "; //Horizontal Print
            }
            cout << "\n";
        }
    }

    int getPosition(int x, int y){
        // Obtain the position representated with single dimension (X*Y) using two-dimensional axis (X,Y).[1,2,3,4,5,6] = [[1,2],[3,4],[5,6]] 
        return x + y * width;
    }

    char getWallSymbol() {
        return WALL_SYMBOL;
    }

    char getCorridorSymbol() {
        return CORRIDOR_SYMBOL;
    }

    // private class methods
    private:

    char WALL_SYMBOL='#';
    char CORRIDOR_SYMBOL=' ';

    void initWalls() {
        std::fill_n(array2D, width*height, WALL_SYMBOL); // set all walls
    }

    void recursiveAlgorithm(int x, int y) {
        // https://stackoverflow.com/questions/38502/whats-a-good-algorithm-to-generate-a-maze
        // https://hurna.io/academy/algorithms/maze_generator/recursive_division.html
        
        int direction[4] = {UP,RIGHT,DOWN,LEFT};

        // shuffle: https://stackoverflow.com/questions/922256/c-array-shuffle
        std::random_shuffle(direction, direction + (sizeof(direction)/sizeof(direction[0])));

        array2D[getPosition(x,y)] = CORRIDOR_SYMBOL; // base

        // Loop to attempt to visit that direction
        for (int i=0 ; i<4; i++){

            //Initialize aux variables
            int dx=0, dy=0;

            switch (direction[i]){
                case UP: dy = -1; break;
                case RIGHT: dx = 1; break;
                case DOWN: dy = 1; break;
                case LEFT: dx = -1; break;
            }

            generatePath(x + dx*2,y + dy*2,dx,dy);

        }
    }

    int isBound (int x, int y) {
        return !(x < 0 || y < 0 || x >= width  || y >= height);
    }

    void generatePath(int x,int y, int dx, int dy) {
        if (isBound(x, y) && array2D[getPosition(x, y)] == WALL_SYMBOL) {
            array2D[getPosition(x-dx, y-dy)] = CORRIDOR_SYMBOL;
            recursiveAlgorithm(x, y); // restart
        }
    }

    void avoidEndPath() {
        
        for (int y = 1 ; y < height-1; y++) {
            if (y%3==0) {
                for (int x= 1 ; x < width; x++)
                    if (isBound(x, y))
                       array2D[getPosition(x,y)] = CORRIDOR_SYMBOL;
            }
        }
        
        for (int x = 2; x < width-2; x++) {
            if (x%3==0) {
                for (int y = 1; y < height-1 ; y++)
                    if (isBound(x, y))
                        array2D[getPosition(x,y)] = CORRIDOR_SYMBOL;
            }
        }
    }

    void setRoom () {
        int ycenter = floor(height/2);
        int xcenter = floor(width/2);

        for (int i = (xcenter-5) ; i < xcenter+5; i++) {
            for (int j = (ycenter-3) ; j <= (ycenter+2); j++) {
                
                if ((i == (xcenter-4) && j != (ycenter-3) && j != (ycenter+2)) || (j == (ycenter+1) && i != (xcenter-5)) || (i == (xcenter-3) && j == (ycenter-2)) || (i == (xcenter-2) && j == (ycenter-2))) {
                    array2D[getPosition(i, j)] = WALL_SYMBOL;
                }
                else{
                    array2D[getPosition(i, j)] = CORRIDOR_SYMBOL;
                }
                    
            }
        }
    }

    void symmetrization() {
        // https://www.faceprep.in/c/program-to-find-all-symmetric-pairs-in-an-array/

        int blank = ceil(width / 2);
        int draw = floor(width / 2);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < draw; j++) {
                array2D[getPosition((blank+j), i)] = array2D[getPosition((draw-1-j), i)];
            }
        }
    }
};