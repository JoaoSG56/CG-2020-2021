
#ifndef GENERATOR_TRANSFORMS_H
#define GENERATOR_TRANSFORMS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glut.h>
#endif

class Transform{
    float x_value;
    float y_value;
    float z_value;

    public:
        Transform();
        Transform(float x, float y, float z);
        float getX();
        float getY();
        float getZ();
        virtual void execute(){ };

};

class Translation : public Transform{
public:
    Translation();
    Translation(float x, float y, float z);
    void execute();
};

class Rotation : public Transform{
    float angle;
public:
    Rotation();
    Rotation(float a, float x, float y, float z);
    void execute();
};

class Scale : public Transform{
public:
    Scale();
    Scale(float x, float y, float z);
    void execute();
};




#endif //GENERATOR_TRANSFORMS_H
