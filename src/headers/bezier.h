#ifndef GENERATOR_BEZIER_H
#define GENERATOR_BEZIER_H

#include "point.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Patch{
    vector<Point*> controlPoints;

public:
    Patch();
    Patch(vector<Point*>);
    vector<Point*> getCPoints();
    void addPoint(Point*);
};

int bezierParser(int tess,string filePath, string nameFile);

#endif


