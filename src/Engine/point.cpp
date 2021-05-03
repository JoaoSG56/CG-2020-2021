
#include "../headers/point.h"

Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

float Point::getX() {
    return x;
}

float Point::getY() {
    return y;
}

float Point::getZ() {
    return z;
}

void Point::setX(float a) {
    x = a;
}
void Point::setY(float b) {
    y = b;
}
void Point::setZ(float c) {
    z = c;
}

Point* Point::getNormal(Point* p) {
    float l, coordX, coordY, coordZ;

    l = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);
    coordX = p->x / l;
    coordY = p->y / l;
    coordZ = p->z / l;

    return new Point(coordX, coordY, coordZ);
}