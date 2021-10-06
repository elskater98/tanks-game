/*
[Additional Information]
    - Symbol ‘#’ represents a “wall” 
    - Symbol ' ' represents a “corridor”

    - link of interest: https://pragprog.com/titles/jbmaze/mazes-for-programmers/
*/

// Libraries
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm> // std::random_shuffle
#include <vector>

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
    char *array2D; // https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

    // initMap
    void create(int _width, int _height) {
        width=_width;
        height=_height;
        array2D = new char [(int)width*(int)height];

        initWalls();
        recursiveAlgorithm(1,1);
        removeMazeWalls();
        //avoidEndPath();
        //symmetrization();
    }

    void print() {
        cout << "Rows:"<<  width << " Columns:" << height << "\n\n";
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                cout << array2D[getPosition(i,j)] << " "; //Horizontal Print
            }
            cout << "\n";
        }
    }

    int getPosition(int x, int y) {
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
        // http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
        
        int direction[4] = {UP,RIGHT,DOWN,LEFT};

        // shuffle: https://stackoverflow.com/questions/922256/c-array-shuffle
        std::random_shuffle(direction, direction + (sizeof(direction)/sizeof(direction[0])));

        array2D[getPosition(x,y)] = CORRIDOR_SYMBOL; // base

        // Loop to attempt to visit that direction
        for (int i=0 ; i<4; i++){

            //Initialize aux variables
            int dx=0, dy=0;

            switch (direction[i]) {
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

    void generatePath(int x, int y, int dx, int dy) {
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

    bool removeWall(int x, int y) {
        // remove wall if possible.
        bool evenRow = ((y % 2) == 0);
        bool evenIndex = ((x % 2) == 0);

        // check
        if(array2D[getPosition(x, y)] != WALL_SYMBOL) {
            return false;
        }

        if (!evenRow && evenIndex) {
            // Uneven row and even column

            bool hasTop = (y - 2 > 0) && (array2D[getPosition(x, y-2)] == WALL_SYMBOL);
            bool hasBottom = (y + 2 > 0) && (array2D[getPosition(x, y+2)] == WALL_SYMBOL);

            if (hasTop && hasBottom) {
                array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                return true;
            } else if (!hasTop && hasBottom) {
                bool left = (array2D[getPosition(x-1, y-1)] == WALL_SYMBOL);
                bool right = (array2D[getPosition(x+1, y-1)] == WALL_SYMBOL);
                if (left || right) {
                    array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                    return true;
                }
            } else if (!hasBottom && hasTop) {
                bool left = (array2D[getPosition(x-1, y+1)] == WALL_SYMBOL);
                bool right = (array2D[getPosition(x+1, y+1)] == WALL_SYMBOL);
                if (left || right) {
                    array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                    return true;
                }
            }
        } else if (evenRow && !evenIndex) {
            // Even row and uneven column
            bool hasLeft = (array2D[getPosition(x-2, y)] == WALL_SYMBOL);
            bool hasRight = (array2D[getPosition(x+2, y)] == WALL_SYMBOL);

            if (hasLeft && hasRight) {
                array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                return true;
            } else if (!hasLeft && hasRight) {
                bool top = (array2D[getPosition(x-1, y-1)] == WALL_SYMBOL);
                bool bottom = (array2D[getPosition(x-1, y+1)] == WALL_SYMBOL);
                if (top || bottom) {
                    array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                    return true;
                }
            } else if (!hasRight && hasLeft) {
                bool top = (array2D[getPosition(x+1, y-1)] == WALL_SYMBOL);
                bool bottom = (array2D[getPosition(x+1, y+1)] == WALL_SYMBOL);
                if (top || bottom) {
                    array2D[getPosition(x, y)] = CORRIDOR_SYMBOL;
                    return true;
                }
            }
        }
        return false;
    }

    // https://github.com/keesiemeijer/maze-generator
    void removeMazeWalls() {
        /*if (!this.removeWalls || !this.matrix.length) {
            return;
        }*/

        int min = 0;
        int max = height-1;
        int maxTries = 100;
        int tries = 0;

        int wallsRemoved = 0;

        while (tries < maxTries) {
            tries++;

            if (wallsRemoved >= maxTries) { // is goal achieved?
                break;
            }

            // Get random row from array2D
            int y = floor(((float)rand() / (float)RAND_MAX) * (max-min+1)) + min;
            if (y == min) {
                y = y + 1;
            } else if (y == max) {
                y = y - 1;
            }
            
            /*
            * using std:vector instead of array,
            * to work with it as a STACK when requiring dynamics push
            * at first the size is not know 
            */
            std::vector<int> walls_vector;

            // fixed y, only saving x coordinate
            for (int x = 1; x < width-2; x++) {
                if(array2D[getPosition(x, y)] == WALL_SYMBOL) {
                    walls_vector.push_back(x);
                }
            }

            // shuffle walls randomly
            std::random_shuffle(walls_vector.begin(), walls_vector.end());

            for (int i = 0; i < walls_vector.size(); i++) {
                if(removeWall(walls_vector[i], y)) {
                    wallsRemoved++;
                    break;
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