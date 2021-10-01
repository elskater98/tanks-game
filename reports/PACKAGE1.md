# Work Package 1

This package is focused on introducing us to the opengl libraries, and how to display basic figures via its methods.

The idea starts from creating an algorithm to generate a random map for a pacman game, using c++. In this way, from the data-structure that models the map, we will be able to perform its corresponding visualitzation through opengl libraries.

## Generate Random Map

We searched over the internet for algorithms to generate random maps, and we got different techniques with at least one path based on the typical graph-search algorithms such as Binary Tree, Depth/Breadth First Search, Kruska'ls, Prim's, recursive backtracking, recursive division and sidewinder.

Overall, we found the recursive backtracking is straighforward and commonly used for maze generation. Thus, we finally got a good way to develop this piece of code comparing among the difficulties of others.

But it's true, you’ll need enough memory to store the entire maze in memory, as it requires stack space again proportional to the size of the maze. Meaning, for very large mazes it can be fairly inefficient. But for most mazes, it works a charm. The ones we expect to perform.

Basically, this algorithm is based on the single path premise, starting at a specific point and randomly choose the path to follow considering non-visited cells, and ending, when the process has backed all the way up to the starting point.

In this way, we assure visiting all cells, and a single path full-connected graph map.

For more information about the backtracking technique, check the following [link](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking). Also, this [link](https://pragprog.com/titles/jbmaze/mazes-for-programmers/) will provide an introduction to maze generations for programmers.


## Code Structure

After explaining the main reason why we choose the Recursive Backtracking algorithm, we will introduce you the code developed in this first package.

First of all, we create a class called *Map*, which mainly contains an empty constructor, a *create()* method to initialize and generate the map, and finally, a *std_out print()* method to view the map on the prompt of the command line.

But, how did we decide to model the Map? 

The class has an array pointer data-structure containing all the elements/cells in a single dimension where walls may be represented as "#" and corridors as " ". Whatever, you may change its config :P

In this way, we already got a Map object with its properties and methods to work with, some of which are detailed below.

## .create()

Set to initialize and generate the map, all by following the next steps.

- ### 1 .initWalls()

Just to fullfill the array.

- ### 2 .recursiveAlgorithm(int x, int y)

When the recursive backtracking is applied.

This algorithm uses a random shuffle of the directions {UP, DOWN, LEFT, RIGHT} at each step to choose ramdonly the path, but setting a CORRIDOR_SYMBOL by default in the current position.

Also, before stepforward we check the boundaries of the map, so thus, be able to recalculate the next point to set a new corridor.

- ### 3 .avoidEndPath()

After generating the map with only one single path we decide to create a method to avoid end paths. 

This method loops all the maps in X and Y, to set corridors. Also, we set the location of the second character of this game in the centre of the map.

- ### 4 .setRoom()

Just to calculate and establish the commonly known room of ghost in pacman games.

- ### 5 .simetrization()

Finally, we decided to use symmetrization to avoid path problems and get a more aesthetic maze. Simply by copying one side into the other.


## Main program

Regarding the main program, it uses the Map class to generate the map and visualize it via opengl libraries.

First of all, the map is created using the width and height passed by the user, and after that, the map is visualized thanks to the GLUT library procedures.

To visualize the map we init the GLUT library with the position and size of the window. Also, we perform a loop through the map for each axis and set for each cell (wall or corridor) the corresponding GL_QUAD (square). 

Color blue for walls, and black for corridors. Not too complicated :P

Well, don't forget to swap the buffers!!