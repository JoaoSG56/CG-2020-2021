
#include "../headers/Point.h"

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