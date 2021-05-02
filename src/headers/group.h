
#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include <vector>
#include "figure.h"
#include "transforms.h"


class Group {
    std::vector<Transform*> transforms;
    std::vector<Figure*> figures;
    std::vector<Group*> childs;
    float R, G, B;

    public:
        Group();
        Group(std::vector<Transform*> t, std::vector<Figure*> f, std::vector<Group*> c);
        std::vector<Transform*> getTransforms();
        std::vector<Figure*> getFigures();
        std::vector<Group*> getChilds();
        void pushTransform(Transform* t);
        void pushFigure(Figure* f);
        void pushGroup(Group* g);
        float getR();
        float getG();
        float getB();
        void setRGB(float,float,float);
};

#endif //GENERATOR_GROUP_H
