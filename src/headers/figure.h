#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "point.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include "/usr/local/include/IL/il.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#endif

class Figure{
    private:
        float buffer_size[3];
        GLuint buffer1,buffer2,buffer3,texture;
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float emissive[4];
        float shin;

    public:
        Figure();
        void setUp(vector<Point*>, vector<Point*>,vector<Point*>);
        void loadTexture(string file);
        void addMaterials(float diff[4], float spec[4], float emiss[4], float amb[4], float shine);
        void draw();
};

#endif //GENERATOR_FIGURES_H
