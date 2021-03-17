#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "vertex.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Figure{
    private:
        std::vector<Vertex*> vertexes;

    public:
        void pushVertex(Vertex* v);
        int getSize();
        std::vector<Vertex*> getVertexes();
        void draw(GLenum mode);
};

#endif //GENERATOR_FIGURES_H
