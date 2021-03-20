#include "../headers/figure.h"

using std::vector;

void Figure::pushVertex(Point *v) {
    vertexes.push_back(v);
}

int Figure::getSize() {
    return vertexes.size();
}

vector<Point *> Figure::getVertexes() {
    return vertexes;
}

void Figure::draw(GLenum mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    vector<Point *> v = getVertexes();

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < getSize(); i++) {
        glVertex3f(v[i]->getX(), v[i]->getY(), v[i]->getZ());
    }

    glEnd();

}