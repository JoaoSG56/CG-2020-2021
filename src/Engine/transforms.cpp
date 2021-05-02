
#include "../headers/transforms.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <stdlib.h>
#include <GL/glut.h>
#endif
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
    up[0] = 0;
    up[1] = 1;
    up[2] = 0;
}

void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; j++) {
        res[j] = 0;
        for (int k = 0; k < 4; k++) {
            res[j] += v[k] * m[k * 4 + j];
        }
    }
}


void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

float length(float* v) {

    float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return res;

}

void curveRotate(float* deriv, float* up) {
    float esq[3];

    cross(deriv, up, esq);
    cross(esq, deriv, up);

    normalize(deriv);
    normalize(up);
    normalize(esq);

    float m[4][4] = {
            {deriv[0], deriv[1], deriv[2], 0},
            {up[0],    up[1],    up[2],    0},
            {esq[0],   esq[1],   esq[2],   0},
            {0.0f,     0.0f,     0.0f,     1}
    };
    glMultMatrixf((float*) m);
}

void getCatmullRomPoint(float t, int* indices, float* p, float* deriv, std::vector<Point*> points) {
    // catmull-rom matrix
    float m[4][4] = {{-0.5f, 1.5f,  -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f,  -0.5f},
                     {-0.5f, 0.0f,  0.5f,  0.0f},
                     {0.0f,  1.0f,  0.0f,  0.0f}};

    float tt[4] = {t * t * t, t * t, t, 1};
    float dtt[4] = {3 * t * t, 2 * t, 1, 0};
    float res[4];
    float deriv_aux[4];


    multMatrixVector((float*) m, tt, res);

    multMatrixVector((float*) m, dtt, deriv_aux);

    Point* p0 = points[indices[0]];
    Point* p1 = points[indices[1]];
    Point* p2 = points[indices[2]];
    Point* p3 = points[indices[3]];


    // T*M*P
    p[0] = res[0] * p0->getX() + res[1] * p1->getX() + res[2] * p2->getX() + res[3] * p3->getX();
    p[1] = res[0] * p0->getY() + res[1] * p1->getY() + res[2] * p2->getY() + res[3] * p3->getY();
    p[2] = res[0] * p0->getZ() + res[1] * p1->getZ() + res[2] * p2->getZ() + res[3] * p3->getZ();


    deriv[0] = deriv_aux[0] * p0->getX() + deriv_aux[1] * p1->getX() + deriv_aux[2] * p2->getX() +
               deriv_aux[3] * p3->getX();
    deriv[1] = deriv_aux[0] * p0->getY() + deriv_aux[1] * p1->getY() + deriv_aux[2] * p2->getY() +
               deriv_aux[3] * p3->getY();
    deriv[2] = deriv_aux[0] * p0->getZ() + deriv_aux[1] * p1->getZ() + deriv_aux[2] * p2->getZ() +
               deriv_aux[3] * p3->getZ();

}

void getGlobalCatmullRomPoints(float gt, float* p, float* deriv, std::vector<Point*> points) {
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

    getCatmullRomPoint(t, indices, p, deriv, points);

}

void Translation::constructCurve() {
    float p[3];
    float deriv[3];
    for (int t = 0; t < 100; t++) {
        getGlobalCatmullRomPoints((float) t / 100, p, deriv, catmull_points);
        curve_points.push_back(new Point(p[0], p[1], p[2]));
    }
}

int Translation::getCatSize() {
    return catmull_points.size();
}

void Translation::insertPoint(Point* p) {
    catmull_points.push_back(p);
}


void Translation::drawCurve() {
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < curve_points.size(); i++) {
        glVertex3f(curve_points[i]->getX(), curve_points[i]->getY(), curve_points[i]->getZ());
    }
    glEnd();
}



void Translation::execute() {

    float pos[3];
    float deriv[3];
    if (time > 0) {
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        float globalTime = elapsed / (time * 1000);
        getGlobalCatmullRomPoints(globalTime, pos, deriv, catmull_points);
        glTranslatef(pos[0],pos[1],pos[2]);
        curveRotate(deriv, up);
    } else
        glTranslatef(getX(), getY(), getZ());
}


/* Rotation */
Rotation::Rotation(float a, float x, float y, float z, float t) : Transform(x, y, z) {
    angle = a;
    time = t;
}

void Rotation::execute() {
    float ang = angle;

    if (time > 0) {
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        ang = (elapsed * 360) / (time * 1000);
    }

    glRotatef(ang, getX(), getY(), getZ());
}


/* Scale */
Scale::Scale(float x, float y, float z) : Transform(x, y, z) {
}

void Scale::execute() {
    glScalef(getX(), getY(), getZ());
}

