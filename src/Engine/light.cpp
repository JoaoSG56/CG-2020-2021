#include "../headers/light.h"

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

void Light::draw(){

}