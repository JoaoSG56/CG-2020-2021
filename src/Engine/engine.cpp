
#ifdef __APPLE__

#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "headers/tinyxml2.h"
#include <vector>
#include <string>
#include <iostream>

struct Ponto {
    double x;
    double y;
    double z;
};

using namespace tinyxml2;
using namespace std;

string XMLPath = "../src/Engine/"; // for now
string figures3dPath = "../src/Figures/"; // for now
float ex = 5, ey = 5, ez = 5;
float tx = 0, ty = 0, tz = 0;
float xsize = 1, size = 1, zsize = 1;
float angleX = 1, angleY = 1;

vector<Ponto> vertices;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(ex, ey, ez,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

// put the geometric transformations here
    glTranslatef(tx, ty, tz); // moves the object
    glScalef(xsize, size, zsize); // scale factors for each axis
    glRotatef(angleY, 0, 1, 0); // angle is in degrees
    glRotatef(angleX, 1, 0, 0);


// put drawing instructions here
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    // vector drawn
    glColor3f(1, 1, 1);

    for (int i = 1; i < vertices.size(); i++)
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

    glEnd();

    // End of frame
    glutSwapBuffers();
}

void keyboardspecial(int key_code, int x, int y){
    switch (key_code) {
        case GLUT_KEY_UP:
            angleY +=1;
            break;
        case GLUT_KEY_DOWN:
            angleY -=1;
            break;
        case GLUT_KEY_RIGHT:
            angleX+=1;
        case GLUT_KEY_LEFT:
            angleX-=1;
    }
    glutPostRedisplay();
}

// write function to process keyboard events
void keyboardfunc(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            size += 0.1;
            break;
        case '-':
            size -= 0.1;
            break;
        case 'z':
            zsize += 0.1;
            break;
        case 'x':
            zsize -= 0.1;
            break;
        case 'c':
            xsize += 0.1;
            break;
        case 'v':
            xsize -= 0.1;
            break;
        case 'w':
            tz += 0.1;
            break;
        case 's':
            tz -= 0.1;
            break;
        case 'a':
            tx += 0.1;
            break;
        case 'd':
            tx -= 0.1;
            break;
        case 'k':
            ty += 0.1;
            break;
        case 'j':
            ty -= 0.1;
            break;
    }
    glutPostRedisplay();
}


void readfile(string ficheiro){
    string delimiter = " ";

}

void readXML(string file){
    XMLDocument xmldoc;
    if(!(xmldoc.LoadFile(("../src/Engine/" + file).c_str()))){
        XMLElement * pRootElement = xmldoc.FirstChildElement();
        for(XMLElement *element = pRootElement->FirstChildElement(); element != NULL; element = element->NextSiblingElement()){
            string ficheiro = element -> Attribute("file");
            cout << "Ficheiro: " << ficheiro << " lido com sucesso " << endl;
            readfile(figures3dPath + ficheiro);
        }
    }

}

int main(int argc, char **argv) {
    readXML("teste.xml");
    /*
// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardfunc);
    glutSpecialFunc(keyboardspecial);


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();
     */

    return 1;
}
