#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <unistd.h>

/**
* Class which simplifies the use of glMaterialfv,
* when the lighting mode is enabled.
*/

class LightMaterial {
    public:
        GLint position[4] = {0, 0, 0, 0};
        GLfloat color[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat diffuseLight[4] = {0.8f, 0.8f, 0.8f, 1.0f}; //{0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat specularLight[4]= {0.5f, 0.5f, 0.5f, 1.0f};//{0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat emission[4] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat shininess = 1;

    void apply() {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->color); // GL_FRONT_AND_BACK
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->diffuseLight);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->specularLight);
        //glMaterialfv(GL_FRONT, GL_EMISSION, this->emission);
        //glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
    }
};