
#include "../headers/vertex.h"

Vertex::Vertex() {
    x = 0;
    y = 0;
    z = 0;
}

Vertex::Vertex(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

float Vertex::getX() {
    return x;
}

float Vertex::getY() {
    return y;
}

float Vertex::getZ() {
    return z;
}

void Vertex::setX(float a) {
    x = a;
}
void Vertex::setY(float b) {
    y = b;
}
void Vertex::setZ(float c) {
    z = c;
}