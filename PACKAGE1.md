# PACKAGE 1
## Introduction
In this package, we have the aim to generate a random map using c++ and visualize the map created with OpenGL.

## Generate Random Map
First of all, we search different algorithms to generate random maps and we found different techniques to generate a random map with at least one path. For example Binary Tree, Depth First Search, Kruskal's, Prim's, recursive division and sidewinder. All of them, have in common are search algorithms. 

Finally, we decide to use recursive division to generate the single path. It is because we found a good way to develop this piece of code comparing the difficulties of others.

After explaining the main reason why we choose the Recursive Division algorithm, we explain the code developed in this first package.

First of all, we create a class called Map, which contain an empty constructor, create a method to generate the random map and a print method to view the map on the prompt of the command line. The other methods developed in this class are private.

## .create()
First of all, it completes the array (this array is a pointer that has all the elements in a single dimension, we use a method to use this using the row and column) with walls ("#") and create the main path using the Recursive Division Algorithm. This algorithm uses a random shuffle of the directions (UP, DOWN, LEFT, RIGHT) and set a corridor symbol (' ') in the position passed by parameter, also we check the boundaries of the map and recalculate the next point to set a new corridor.

After generating the map with only one single path we decide to create a method to avoid end paths, this method loops all the maps in X and Y, to set corridors. Also, we set the location of the second character of this game in the centre of the map.

Finally, we decided to use symmetrization to avoid path problems.

## Display Map

This part was the main program, it use the class called before to generate the map and visualize it.

First of all, we create a map using the width and height passed by the user. After that, we create the map that we will visualize.

To visualize the map we init the GLUT library with the position and size of the window. Also, we loop the map for each axis and set the square with the corresponding colour.


