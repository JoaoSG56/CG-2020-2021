#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "point.h"
#ifndef __APPLE__
#include <GL/glew.h>
#endif

class Figure{
    private:
        float buffer_size;
        GLuint buffers[1];

    public:
        Figure();
        void setUp(std::vector<Point*> vertexes);
        void draw();
};

#endif //GENERATOR_FIGURES_H
