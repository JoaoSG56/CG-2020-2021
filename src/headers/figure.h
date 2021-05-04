#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "point.h"
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Figure{
    private:
        float buffer_size[2];
        GLuint buffer1,buffer2;

    public:
        Figure();
        void setUp(std::vector<Point*> vertexes, std::vector<Point*> normal);
        void draw();
};

#endif //GENERATOR_FIGURES_H
