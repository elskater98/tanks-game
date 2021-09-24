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

    // Create Map
    Map map = Map(input_width,input_heigth);



    exit(0);
}