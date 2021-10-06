# Work Package 2

The second work package is composed of the following tasks:

- Inclusion of a starting point for the main and the enemy characters.
- Inclusion and animation of the main character.
- Inclusion and animation of the enemy character.

### Task 1. Include the starting points.

- the starting point of the main character will be upper left square, 
- and the one for the enemy character will be the lower right.

We just calculate the points when displaying the map, thus,
we are able to print the squares with its corresponding color.

### Animation.

For animate both, the main character and the enemy one we used the **idle()** callback function, 
hence, when integrating each of the characters the movement may be represented by the following uniform movement formulas:

    x = x + vx * t;
    y = y + vy * t;

where *t* is the time, and *vx*, *vy* correspont to the velocity vector of each direction,

in this way, each of the characters coordinates are represented by time instant.

### Task 2: Main character animation

- it moves from the center of a square to the center of a contiguous one.
- movements are indicated through the keyboard.
- it cannot move to a square occupied by the enemy character.

### Task 3: Enemy character animation

- its movements are decided autonomously.
- it moves from the center of a square to the center of a contiguous one.
- implement it as an intelligent agent that makes its own decisions.
- cannot move to a square occupied by the main character.