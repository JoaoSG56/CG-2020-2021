#include "../headers/camera.h"

Camera::Camera() {
    position = new Point(10, 5, 10);
    direction = new Point(0, 0, 0);
    yaw = -M_PI_4;
    pitch = 8.1;
    speed = 0.5;
    rotationSpeed = 0.0005;
    alphaStatic = 0;
    betaStatic = 0;
}

Point *Camera::getPosition() {
    return position;
}

Point *Camera::getDirection() {
    return direction;
}

Point *Camera::getStaticPosition() {
    float r = sqrt(pow(position->getX(), 2) + pow(position->getY(), 2) + pow(position->getZ(), 2));
    return new Point(r * cos(alphaStatic) * sin(betaStatic),
                     r * sin(alphaStatic),
                     r * cos(alphaStatic) * cos(betaStatic));
}

Point *Camera::getFocus() {
    return new Point(position->getX() + direction->getX(), position->getY() + direction->getY(),
                     position->getZ() + direction->getZ());
}

void Camera::moveFoward() {
    position->setX(position->getX() + direction->getX() * speed);
    position->setY(position->getY() + direction->getY() * speed);
    position->setZ(position->getZ() + direction->getZ() * speed);
}


void Camera::moveBackwards() {
    position->setX(position->getX() - direction->getX() * speed);
    position->setY(position->getY() - direction->getY() * speed);
    position->setZ(position->getZ() - direction->getZ() * speed);
}

void Camera::moveLeft() {
    position->setX(position->getX() + direction->getZ() * speed);
    position->setZ(position->getZ() - direction->getX() * speed);
}

void Camera::moveRight() {
    position->setX(position->getX() - direction->getZ() * speed);
    position->setZ(position->getZ() + direction->getX() * speed);
}

void Camera::turn(float dx, float dy) {
    yaw += dx * rotationSpeed;
    pitch += dy * rotationSpeed;


    direction->setX(sin(pitch) * sin(yaw));
    direction->setY(cos(pitch));
    direction->setZ(-sin(pitch) * cos(yaw));
}

void Camera::turnStatic(unsigned char key) {

    switch (key) {
        case 'w':
            if (alphaStatic < (0.85 * M_PI_2)) {
                alphaStatic += M_PI / 32;
            }
            break;
        case 's':
            if (alphaStatic > (-0.85 * M_PI_2)) {
                alphaStatic -= M_PI / 32;
            }
            break;
        case 'a':
            betaStatic -= M_PI / 32;
            break;
        case 'd':
            betaStatic += M_PI / 32;
            break;
        case '+':
            speed *= 2;
            break;
        case '-':
            speed /= 2;
            break;
        default:
            break;
    }


}


