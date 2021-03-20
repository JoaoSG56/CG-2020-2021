
#ifndef GENERATOR_CAMERA_H
#define GENERATOR_CAMERA_H

#include "point.h"

class Camera{
    private:
        Point* position;
        Point* direction;
        float yaw;
        float pitch;
        float speed;
        float rotationSpeed;
        float alphaStatic;
        float betaStatic;
    public:
        Camera();
        Point* getPosition();
        Point* getDirection();
        Point* getFocus();
        void moveFoward();
        void moveBackwards();
        void moveLeft();
        void moveRight();
        void turn(float,float);
        void turnStatic(unsigned char);
        Point* getStaticPosition();
};

#endif //GENERATOR_CAMERA_H
