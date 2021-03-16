#ifndef GENERATOR_FIGURES_H
#define GENERATOR_FIGURES_H

#include <vector>
#include "point.h"
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Figure{
    private:
        std::vector<Point*> vertexes;

    public:
        void pushVertex(Point* v);
        int getSize();
        std::vector<Point*> getVertexes();
};

#endif //GENERATOR_FIGURES_H
