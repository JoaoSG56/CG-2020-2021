
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <string>
#include "Point.h"

#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Camera{
    Point* cameraPosition;
    Point* cameraTilt;
    Point* cameraFacing;

    public:
        Camera();
        void move();


        Point* getPosition();
        Point* getTilt();
        Point* getFacing();

        void setPosition(Point*);
        void setTilt(Point*);
        void setFacing(Point*);

};

#endif