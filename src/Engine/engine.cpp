
#ifdef __APPLE__

#include <GLUT/glut.h>


#else
#include <GL/glut.h>
#endif

#include <cmath>
#include "../headers/tinyxml2.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../headers/Point.h"
#include <regex>


using namespace tinyxml2;
using namespace std;

string XMLPath = "../src/Files/"; // for now
string figures3dPath = "../src/Files/"; // for now


float alpha = 0;
float beta = 0;
float raioCamera = 8;
GLenum mode = GL_FILL;

vector<Point> vertices;

void eixos() {
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
    glEnd();
}

void drawVertex(int x, int y, int z) {
    glVertex3f(x, y, z);
}

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
    gluLookAt(raioCamera * cos(alpha) * sin(beta), raioCamera * sin(alpha), raioCamera * cos(alpha) * cos(beta),
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);
    eixos();

// put the geometric transformations here
    glPolygonMode(GL_FRONT,mode);

// put drawing instructions here
    glBegin(GL_TRIANGLES);
    // vector drawn
    int size = vertices.size();
    for (int i = 0; i < size; i++) {
        if (i % 3 == 0) {
            glColor3f(((float) (rand() % 100) / 100.0), ((float) (rand() % 100) / 100.0),
                      ((float) (rand() % 100) / 100.0));
        }
        glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
        //printf("%f %f %f\n",vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }

    glEnd();

    // End of frame
    glutSwapBuffers();
}

void keyboardspecial(int key_code, int x, int y) {
    switch (key_code) {

        case GLUT_KEY_UP:
            raioCamera -= 1;
            break;
        case GLUT_KEY_DOWN:
            raioCamera += 1;
            break;
            /*
        case GLUT_KEY_RIGHT:
            angleX += 1;
        case GLUT_KEY_LEFT:
            angleX -= 1;
             */

    }
    glutPostRedisplay();
}

// write function to process keyboard events
void keyboardfunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            if (alpha < (0.9 * M_PI_2)) {
                alpha += M_PI / 32;
            }
            break;
        case 's':
            if (alpha > (-0.9 * M_PI_2)) {
                alpha -= M_PI / 32;
            }
            break;
        case 'a':
            beta -= M_PI / 32;
            break;
        case 'd':
            beta += M_PI / 32;
            break;
        case 'p':
            mode = GL_POINT;
            break;
        case 'l':
            mode = GL_LINE;
            break;
        case 'f':
            mode = GL_FILL;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void readfile(string ficheiro) {
    string delimiter = " ";
    ifstream inputFileStream(ficheiro);
    int count;
    inputFileStream >> count;
    inputFileStream.ignore(1, '\n');

    for (int i = 0; i < count; i++) {
        string line;
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a, b, c;
        getline(lineStream, a, ' ');
        getline(lineStream, b, ' ');
        getline(lineStream, c, ' ');


        vertices.push_back(*new Point(atof(a.c_str()), atof(b.c_str()), atof(c.c_str())));

    }
}

int readXML(string file) {
    XMLDocument xmldoc;
    if (!(xmldoc.LoadFile((XMLPath + file).c_str()))) {
        XMLElement *pRootElement = xmldoc.FirstChildElement();

        for (XMLElement *element = pRootElement->FirstChildElement(); element; element = element->NextSiblingElement()) {
            string ficheiro = element->Attribute("file");
            cout << "Ficheiro: " << ficheiro << " lido com sucesso " << endl;
            readfile(figures3dPath + ficheiro);
        }
        return 1;
    } else {
        return 0;
    }

}

int main(int argc, char **argv) {

    if(argc != 2 || !regex_match(argv[1],regex("([a-zA-Z0-9\-_])+\.xml"))){
        cout << "Argumentos inválidos\nComando:>> ./engine {file.xml}" << endl;
        exit(0);
    }
    if(!readXML(argv[1])){
        cout << "Ficheiro Inválido ou Mal escrito\nCertificar que o ficheiro se encontra em /src/Files/" << endl;
        exit(0);
    }

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@2020-2021");

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


    return 0;
}
