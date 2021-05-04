#ifndef GENERATOR_LIGHT_H
#define GENERATOR_LIGHT_H

#include "point.h"
enum Type {POINT,DIRECTIONAL,SPOT};
class Light {
    Point* point;
    Type type;

    public:
        Light();
        Light(Type,Point*);
        Type getType();
        Point* getPoint();
        void setPoint(Point* p);
        void render();
};


#endif //GENERATOR_LIGHT_H
