#include "../headers/camera.h"
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <stdlib.h>
#include <GL/glut.h>
#endif

Camera::Camera() {
    position = new Point(10, 5, 10);
    direction = new Point(0, 0, 0);

}
Camera::Camera(float camx,float camy,float camz) {
    position = new Point(camx, camy, camz);
    direction = new Point(0, 0, 0);

}
Camera::Camera(float camx,float camy,float camz,
               float dirx,float diry,float dirz) {
    position = new Point(camx, camy, camz);
    direction = new Point(dirx, diry, dirz);

}

void Camera::setPosition(float a , float b , float c ) {
    position = new Point(a,b,c);
}

Point *Camera::getPosition() {
    return position;
}

Point *Camera::getDirection() {
    return direction;
}

Point *Camera::getFocus() {
    return new Point(position->getX() + direction->getX(), position->getY() + direction->getY(),
                     position->getZ() + direction->getZ());
}

CameraFPS::CameraFPS() : Camera() {
    yaw = -M_PI_4;
    pitch = 8.1;
    speed = 0.5;
    rotationSpeed = 0.0005;
}


void CameraFPS::move(unsigned char key){
    Point* position = getPosition();
    Point* direction = getDirection();
    switch (key) {
        case 'w' :
            position->setX(position->getX() + direction->getX() * speed);
            position->setY(position->getY() + direction->getY() * speed);
            position->setZ(position->getZ() + direction->getZ() * speed);
            break;
        case 's':
            position->setX(position->getX() - direction->getX() * speed);
            position->setY(position->getY() - direction->getY() * speed);
            position->setZ(position->getZ() - direction->getZ() * speed);
            break;
        case 'd':
            position->setX(position->getX() - direction->getZ() * speed);
            position->setZ(position->getZ() + direction->getX() * speed);
            break;
        case 'a':
            position->setX(position->getX() + direction->getZ() * speed);
            position->setZ(position->getZ() - direction->getX() * speed);
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

void CameraFPS::turn(float dx, float dy) {
    Point* direction = getDirection();
    yaw += dx * rotationSpeed;
    pitch += dy * rotationSpeed;


    direction->setX(sin(pitch) * sin(yaw));
    direction->setY(cos(pitch));
    direction->setZ(-sin(pitch) * cos(yaw));
}


CameraStatic::CameraStatic() : Camera(){
    alpha=0;
    beta=45;
    speed = 0.5;
}


Point* CameraStatic::getPosition() {
    Point* position = Camera::getPosition();
    float r = sqrt(pow(position->getX(), 2) + pow(position->getY(), 2) + pow(position->getZ(), 2));
    return new Point(r * cos(alpha) * sin(beta),
                     r * sin(alpha),
                     r * cos(alpha) * cos(beta));
}

Point* CameraStatic::getFocus() {
    return Camera::getDirection();
}

void CameraStatic::move(unsigned char key) {

    switch (key) {
        case 'w':
            if (alpha < (0.85 * M_PI_2)) {
                alpha += M_PI / 32;
            }
            break;
        case 's':
            if (alpha > (-0.85 * M_PI_2)) {
                alpha -= M_PI / 32;
            }
            break;
        case 'a':
            beta -= M_PI / 32;
            break;
        case 'd':
            beta += M_PI / 32;
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

void CameraStatic::specialKey(int key_code) {
    printf("entrou\n");
    Point* position = Camera::getPosition();
    float r = sqrt(pow(position->getX(), 2) + pow(position->getY(), 2) + pow(position->getZ(), 2));
    switch (key_code) {
        case GLUT_KEY_UP:
            r-=5*speed;
            break;
        case GLUT_KEY_DOWN:
            r+=5*speed;
            break;
        default:
            break;
    }
    Camera::setPosition(r * cos(alpha) * sin(beta),
                     r * sin(alpha),
                     r * cos(alpha) * cos(beta));
}





