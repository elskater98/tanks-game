// Libraries
#include <GL/glut.h>
#include <iostream>

// Own Libraries

#include "map.c++"

// namespace
using namespace std;

int main(int argc,char *argv[]) {

    // Ask map dimensions
    int input_width,input_heigth;

    cout << "Enter width: ";
    cin >> input_width; 

    cout << "Enter height: ";
    cin >> input_heigth; 

    cout << "[INFO] Generating " << input_width << "x" << input_heigth;

    // Create Map and init
    input_width=25; //remove
    input_heigth=25; //remove

    srand(time(NULL)); // Set Seed to geneate random numbers

    Map map = Map(input_width,input_heigth);


    exit(0);
}