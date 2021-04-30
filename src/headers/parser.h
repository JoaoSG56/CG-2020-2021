#ifndef GENERATOR_PARSER_H
#define GENERATOR_PARSER_H

#include "tinyxml2.h"
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include "point.h"
#include <iostream>
#include "group.h"


int readXML(string file, Group* group, vector<Translation*>* orbits);

#endif //GENERATOR_PARSER_H
