#ifndef _MAIN
#define _MAIN

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ostream>
#ifdef __APPLE__
#define OS_Windows 0
#include <glut.h>
#else
#define OS_Windows 1
#include <GL/glut.h>
#endif
#include "tinyxml2.h"

#define PATH "../src/Files/"

using namespace std;
using namespace tinyxml2;

#endif