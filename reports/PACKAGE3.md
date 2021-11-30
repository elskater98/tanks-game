# Work Package 3

The third work package is composed of the following tasks:

- Plot the map in 3D
- Plot the characters as tanks
- Print text to the screen
- Inclusion of texture mapping

### Task 1. Plot the map in 3D

We used the *glOrtho* procedure in order to fullfill our map/maze with 3D figures (squares). Taking into acoount, obviously the cell_width as reference.
Apart from that, we apply the *glPolygonMode* when displaying to identify those polygons not properly orientated when testing.

Moreover, we set the keyboard to face the observer position, even below it. Using the viewer angles, alpha & betha,
we can modify the position thorught the *glutLookAt* procedure.

### Task 2. Represent the characters as tanks

Regarding the tanks, we decided to make it through our own way.
So we build, them based on two orthogonal polygons, the first, which is the biggest, representing the base.
And the second, the turret, which remarks the tank direction by the canyon.

Moreover, we implemented the turning moving adding direction/orientation variables to the characters, and a new state *ROTATE*.
The one enables integrating the movement of rotation.

### Task 3. Print text to the screen

We based our time counter on the *std::chrono::system_clock* utility. So, the idea is got this information to be displayed.

In this way, at each instant of time we obtain a resulting *std::string* to be displayed just like: "Time elapsed: 43s"
Then the idea is to iterate over this string and add to OpenGL each character via *glutBitmapCharacter*

### Task 4. Inclusion of texture mapping

We used real photograph pictures to fill the square polygons of the map, thus, seeing it more realistic.

So first, we loaded the textures by reading the .jpeg files, in this way OpenGL will be able to apply them.
Then, into the display we simply enable via *glEnable* the corresponing binded texture by *glBindTexture* when required.