# Work Package 4

The third work package is composed of the following tasks:

- Inclusion of lighting effects

#### Requirements:
    
    - Include a light source providing ambient light.
        - The intensity has to be low.
        - Used to avoid those polygons not lighted by some other light source to appear completely black.
    
    - Include a directional light source in front of the main character simulating it carries lights.

    - Optionally, add lights to the enemy character.

### Task 1. Inclusion of lighting effects

For providing an ambient light, first we should enable the lighting mode when displaying de grahic componets using *glEnable(GL_LIGHTING)*.

Then, we should create a new light like *GL_LIGHT0* and setting via the method *glLightfv* its parameters (GLfloat) such as *GL_AMBIENT*, *GL_DIFFUSE* and *GL_SPECULAR*, to enable it later with *glEnable(GL_LIGHT0)*.

In this way, we are getting an ambient light overall elements at the moment *GL_LIGHTING* is enabled, based on the float colors specified as parameters.

Also, is possible to adjust the behaviour of light when treating with materials, thus using *glMaterialfv* remarking the face or faces that should be updated using the parameters *GL_FRONT* or *GL_BACK*.

Regarding the light source for each character, also called *Spotlight*, we just create a new specific light when displaying each character setting the *GL_POSITION* and *GL_SPOT_DIRECTION* among the other parameters also mentioned above.