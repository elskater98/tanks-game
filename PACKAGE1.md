# PACKAGE 1
## Introduction

This package is focused on introducing us to the opengl libraries, and how to display basic figures via its methods.

The idea starts from creating an algorithm to generate a random map for a pacman game, using c++. In this way, from the data-structure that models the map, we will be able to perform its corresponding visualitzation through opengl libraries.

## Generate Random Map

We searched over the internet for algorithms to generate random maps, and we got different techniques with at least one path based on the typical graph-search algorithms such as Binary Tree, Depth/Breadth First Search, Kruska'ls, Prim's, recursive backtracking, recursive division and sidewinder.

Overall, we found the recursive backtracking is straighforward and commonly used for maze generation. Thus, we finally got a good way to develop this piece of code comparing among the difficulties of others.

But it's true, you’ll need enough memory to store the entire maze in memory, as it requires stack space again proportional to the size of the maze. Meaning, for very large mazes it can be fairly inefficient. But for most mazes, it works a charm. The ones we expect to perform.

Basically, this algorithm is based on the single path premise, starting at a specific point and randomly choose the path to follow considering non-visited cells, and ending, when the process has backed all the way up to the starting point.

In this way, we assure visiting all cells, and a single path full-connected graph map.

For more information, check the following [link](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking).


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


