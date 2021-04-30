
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

Translation::Translation(float x, float y, float z, float t) : Transform(x, y, z) {
    time = t;
}

void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; j++) {
        res[j] = 0;
        for (int k = 0; k < 4; k++) {
            res[j] += v[k] * m[k * 4 + j];
        }
    }

}

void getCatmullRomPoint(float t, int* indices, float* p, std::vector<Point*> points) {
    // catmull-rom matrix
    float m[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f,  -0.5f},
                     {-0.5f, 0.0f,  0.5f,  0.0f},
                     {0.0f,  1.0f,  0.0f,  0.0f}};

    float tt[4] = {t * t * t, t * t, t, 1};

    float res[4];
    /*
    res[0] = tt[0] * m[0][0] + tt[1] * m[1][0] + tt[2] * m[2][0] + tt[3] * m [3][0];
    res[1] = tt[0] * m[0][1] + tt[1] * m[1][1] + tt[2] * m[2][1] + tt[3] * m [3][1];
    res[2] = tt[0] * m[0][2] + tt[1] * m[1][2] + tt[2] * m[2][2] + tt[3] * m [3][2];
    res[3] = tt[0] * m[0][3] + tt[1] * m[1][3] + tt[2] * m[2][3] + tt[3] * m [3][3];
    printf("%f %f %f %f\n",res[0],res[1],res[2],res[3]);
    */

    multMatrixVector((float*) (m), tt, res);


    Point* p0 = points[indices[0]];
    Point* p1 = points[indices[1]];
    Point* p2 = points[indices[2]];
    Point* p3 = points[indices[3]];

    p[0] = res[0] * p0->getX() + res[1] * p1->getX() + res[2] * p2->getX() + res[3] * p3->getX();
    p[1] = res[0] * p0->getY() + res[1] * p1->getY() + res[2] * p2->getY() + res[3] * p3->getY();
    p[2] = res[0] * p0->getY() + res[1] * p1->getZ() + res[2] * p2->getZ() + res[3] * p3->getZ();;

}

void getGlobalCatmullRomPoints(float gt, float* p, std::vector<Point*> points) {
    int size = points.size();
    float t = gt * size; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + size - 1) % size;
    indices[1] = (indices[0] + 1) % size;
    indices[2] = (indices[1] + 1) % size;
    indices[3] = (indices[2] + 1) % size;

    getCatmullRomPoint(t, indices, p, points);

}

void Translation::constructCurve() {
    float p[3];

    for (int t = 0; t < 100; t++) {
        getGlobalCatmullRomPoints((float)t/100,p,cat_p);
        c_p.push_back(new Point(p[0],p[1],p[2]));
    }
}

int Translation::getCatSize(){
    return cat_p.size();
}

void Translation::insertPoint(Point* p){
    cat_p.push_back(p);
}

void Translation::drawCurve(){
    glBegin(GL_LINE_LOOP);

    for(int i = 0; i<c_p.size();i++){
        glVertex3f(c_p[i]->getX(),c_p[i]->getY(),c_p[i]->getZ());
    }
    glEnd();
}

void Translation::execute() {

    float pos[3] = {getX(), getY(), getZ()};

    if(time > 0){
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);

        getGlobalCatmullRomPoints(elapsed/(time*1000),pos,cat_p);
    }


    glTranslatef(pos[0], pos[1], pos[2]);
}


/* Rotation */
Rotation::Rotation(float a, float x, float y, float z) : Transform(x, y, z) {
    angle = a;
}

void Rotation::execute() {
    glRotatef(angle, getX(), getY(), getZ());
}


/* Scale */
Scale::Scale(float x, float y, float z) : Transform(x, y, z) {
}

void Scale::execute() {
    glScalef(getX(), getY(), getZ());
}

