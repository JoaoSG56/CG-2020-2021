
#include "../headers/group.h"

Group::Group()= default;

Group::Group(std::vector<Transform*> t, std::vector<Figure*> f, std::vector<Group*> c){
    transforms = t;
    figures = f;
    childs = c;
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