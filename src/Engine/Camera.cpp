
#include "../headers/Camera.h"

Camera::Camera(){
    cameraPosition = new Point(5.0f,5.0f,5.0f);
    cameraFacing = new Point(0.0f,0.0f,0.0f);
    cameraTilt = new Point(0.0f,1.0f,0.0f);
}

void Camera::move() {
    return;
}