
#ifndef GENERATOR_VERTEX_H
#define GENERATOR_VERTEX_H

#include <math.h>
#include <string>

using namespace std;

class Vertex {
    float x;
    float y;
    float z;

    public:
        Vertex();
        Vertex(float, float, float);
        float getX();
        float getY();
        float getZ();
        void setX(float);
        void setY(float);
        void setZ(float);

};


#endif //GENERATOR_VERTEX_H
