
#include "../headers/group.h"

Group::Group() {
    R = 1;
    G = 1;
    B = 1;
}

Group::Group(std::vector<Transform*> t, std::vector<Figure*> f, std::vector<Group*> c){
    transforms = t;
    figures = f;
    childs = c;
    R = 1;
    G = 1;
    B = 1;
}

std::vector<Transform*> Group::getTransforms(){
    return transforms;
}
std::vector<Figure*> Group::getFigures(){
    return figures;
}
std::vector<Group*> Group::getChilds(){
    return childs;
}
void Group::pushTransform(Transform* t){
    transforms.push_back(t);
}
void Group::pushFigure(Figure* f){
    figures.push_back(f);
}
void Group::pushGroup(Group* g){
    childs.push_back(g);
}

float Group::getR() {
    return R;
}
float Group::getG() {
    return G;
}
float Group::getB() {
    return B;
}

void Group::setRGB(float r, float g, float b) {
    R = r;
    G = g;
    B = b;
}