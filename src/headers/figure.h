#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "point.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Figure{
    private:
        int buffer_size;
        GLuint buffers[1];

    public:
        Figure();
        void setUp(std::vector<Point*> vertexes);
        void draw(GLenum);
};

#endif //GENERATOR_FIGURES_H
