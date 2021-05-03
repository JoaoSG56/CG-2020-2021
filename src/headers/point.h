
#ifndef GENERATOR_POINT_H
#define GENERATOR_POINT_H

#include <math.h>
#include <string>

using namespace std;

class Point {
    float x;
    float y;
    float z;

    public:
        Point();
        Point(float, float, float);
        float getX();
        float getY();
        float getZ();
        void setX(float);
        void setY(float);
        void setZ(float);
        static Point* getNormal(Point* p);

};


#endif //GENERATOR_POINT_H
