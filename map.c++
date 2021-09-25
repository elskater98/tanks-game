/*
[Additional Information]
    - Symbol ‘#’ represents a “wall” while spaces are for “corridor”.
*/

// Libraries
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>    // std::random_shuffle
#include <string.h>

// namespace
using namespace std;

// constants
# define UP 0
# define RIGTH 1
# define DOWN 2
# define LEFT 3

class Map{
    public:
    // class properties
    int width;
    int heigth;
    char *array2D; //https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

    // constructor
    Map(int _width, int _heigth){
        width=_width;
        heigth=_heigth;
        array2D = new char [(int)width*(int)heigth];

        // Init array2D with 0
        for(int i=0; i< _width*_heigth;i++){
            array2D[i] = '#';
        }
        recursiveAlgorithm(1,1);
        avoidEndPath();
        symmetrization();
        printMap();
    }

    // class methods
    private:

    void printMap(){
        cout << "Rows:"<<  width << " Columns:" << heigth << "\n\n";
        for(int i=0;i<width;i++){
            for(int j=0;j<heigth;j++){
                cout << array2D[getPosition(j,i)]; //Horizontal Print
            }
            cout << "\n";
        }
    }

    int getPosition(int x, int y){
        //Obtain position of single dimension (X*Y) pointer using two-dimensional axis (X,Y). 
        return x + y * width;
    }


    void recursiveAlgorithm(int x, int y) {
        //https://stackoverflow.com/questions/38502/whats-a-good-algorithm-to-generate-a-maze
        //https://hurna.io/academy/algorithms/maze_generator/recursive_division.html
        
        int direction[4] ={UP,RIGTH,DOWN,LEFT};


        // shuffle the desired direction
        for (int i=0; i<4; ++i) {
            int r = rand() & 3;
            int temp = direction[r];
            direction[r] = direction[i];
            direction[i] = temp;
        }

        array2D[getPosition(x,y)] = ' ';

        // Loop to attempt to visit that direction
        for (int i=0 ; i<4 ; i++){

            //Initialize aux variables
            int dx=0, dy=0;


            switch (direction[i])
            {
                case UP: dy = -1; break;
                case RIGTH: dx = 1; break;
                case DOWN: dy = 1; break;
                case LEFT: dx = -1; break;
            }

            // Aux variables to offset
            int x2 = x + (dx<<1);
            int y2 = y + (dy<<1);

            if (isBound(x2, y2)) {
                if (array2D[getPosition(x2, y2)] == '#') {
                    array2D[getPosition(x2-dx, y2-dy)] = ' ';

                    // repeat recursively
                    recursiveAlgorithm(x2, y2);
                }
            }
            
        }
    }

    int isBound (int x, int y) {
        return !((x < 0 || x >= width) || (y < 0 || y >= heigth));
    }

    void avoidEndPath() {
        
        for (int y = 1 ; y < heigth-1; y++) {
            if (y%3==0) {
                for (int x= 1 ; x < width; x++)
                    if (isBound(x, y))
                       array2D[getPosition(x,y)] = ' ';
            }
        }
        
        for (int x = 2; x < width-2; x++) {
            if (x%3==0) {
                for (int y = 1; y < heigth-1 ; y++)
                    if (isBound(x, y))
                        array2D[getPosition(x,y)] = ' ';
            }
        }
    }

    void symmetrization() {

        int blank = ceil(width / 2);
        int draw = floor(width / 2);

        for (int i = 0; i < heigth; i++) {
            for (int j = 0; j < draw; j++) {
                array2D[getPosition((blank+j), i)] = array2D[getPosition((draw-1-j),i)];
            }
        }
    }
};