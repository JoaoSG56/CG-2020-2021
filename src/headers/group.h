
#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include <vector>
#include "figure.h"
#include "transforms.h"
#include "light.h"


class Group {
    std::vector<Transform*> transforms;
    std::vector<Figure*> figures;
    std::vector<Group*> childs;
    std::vector<Light*> lights;
    float R, G, B;

    public:
        Group();
        Group(std::vector<Transform*>, std::vector<Figure*>, std::vector<Group*>, std::vector<Light*>);
        std::vector<Transform*> getTransforms();
        std::vector<Figure*> getFigures();
        std::vector<Group*> getChilds();
        std::vector<Light*> getLights();

        void pushTransform(Transform* t);
        void pushFigure(Figure* f);
        void pushGroup(Group* g);
        void pushLight(Light* l);

        float getR();
        float getG();
        float getB();
        void setRGB(float,float,float);
};

#endif //GENERATOR_GROUP_H
