
#ifndef GENERATOR_CAMERA_H
#define GENERATOR_CAMERA_H
#define _USE_MATH_DEFINES
#include "point.h"


class Camera{
    private:
        Point* position;
        Point* direction;

    public:
        Camera();
        Camera(float,float,float);
        Camera(float,float,float,float,float,float);

        virtual Point* getPosition();
        Point* getDirection();

        virtual Point* getFocus();
        void setPosition(float,float,float);

        virtual void move(unsigned char){};
        virtual void turn(float, float){};
        virtual void specialKey(int){};

};

class CameraFPS : public Camera{
    float yaw;
    float pitch;
    float speed;
    float rotationSpeed;
public:
    CameraFPS();
    void turn(float,float);
    void move(unsigned char );

};

class CameraStatic : public Camera{
    float alpha;
    float beta;
    float speed;
public:
    CameraStatic();
    void move(unsigned char);
    void specialKey(int key_code);
    Point* getPosition();
    Point* getFocus();

};

#endif //GENERATOR_CAMERA_H
