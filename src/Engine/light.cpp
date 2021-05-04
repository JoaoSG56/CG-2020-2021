#include "../headers/light.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Light::Light() {
}

Light::Light(Type t, Point* p) {
    type = t;
    point = p;
}

Type Light::getType(){
    return type;
}

Point* Light::getPoint() {
    return point;
}

void Light::setPoint(Point* p) {
    point = p;
}

void Light::render(){
    GLfloat ambiente[4] = {0.2,0.2,0.2,1.0};
    GLfloat diff[4] = {1.0,1.0,1.0,0.0};
    GLfloat spec[4] = {1.0,1.0,1.0,1.0};

    float ftype;
    if(type==POINT)
        ftype = 1;
    else if(type == DIRECTIONAL)
        ftype = 0;
    else ftype=1; // ver isto

    GLfloat pos[4] = {point->getX(),point->getY(),point->getZ(),ftype};

    // light position
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    // light colors
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambiente);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diff);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec);

}