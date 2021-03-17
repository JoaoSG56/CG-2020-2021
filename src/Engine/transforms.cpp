
#include "../headers/transforms.h"

Transform::Transform() {
}

Transform::Transform(float x, float y, float z) {
    x_value = x;
    y_value = y;
    z_value = z;
}

float Transform::getX() {
    return x_value;
}

float Transform::getY() {
    return y_value;
}

float Transform::getZ() {
    return z_value;
}

/* Translation */

Translation::Translation(float x, float y, float z) : Transform(x, y, z) {
}

void Translation::execute() {
    glTranslatef(getX(),getY(),getZ());
}


/* Rotation */
Rotation::Rotation(float a,float x, float y, float z) : Transform(x, y, z) {
    angle = a;
}

void Rotation::execute() {
    glRotatef(angle,getX(),getY(),getZ());
}


/* Scale */
Scale::Scale(float x, float y, float z) : Transform(x, y, z) {
}

void Scale::execute() {
    glScalef(getX(),getY(),getZ());
}

