#ifndef GENERATOR_PARSER_H
#define GENERATOR_PARSER_H

#include "tinyxml2.h"
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include "point.h"
#include <iostream>

std::string XMLPath = "../src/Files/"; // for now
std::string figures3dPath = "../src/Files/"; // for now

int readfile(string ficheiro, vector<Point> vertices);
int readXML(string file, vector<Point> vertices);

#endif //GENERATOR_PARSER_H
