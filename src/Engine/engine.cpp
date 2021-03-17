
#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <stdlib.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES


#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "../headers/vertex.h"
#include <regex>
#include "../headers/group.h"
#include "../headers/parser.h"


using namespace tinyxml2;
using namespace std;


float alpha = 0;
float beta = 0;
float raioCamera = 8;
GLenum mode = GL_LINE;

vector<Vertex> vertices;

Group *scene = new Group();

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


void render(Group* group) {
    glPushMatrix();

    vector<Transform*> tranformations = group->getTransforms();
    //for (int i = 0; i < tranformations.size(); i++)
    //    tranformations[i]->execute();

    vector<Figure*> figures = group->getFigures();
    for(int i = 0; i< figures.size();i++)
        figures[i]->draw(mode);

    vector<Group*> children = group->getChilds();
    for(int i = 0; i< children.size();i++)
        render(children[i]);

    glPopMatrix();
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
    //glPolygonMode(GL_FRONT, mode);

// put drawing instructions here
/*
    glBegin(GL_TRIANGLES);
    // vector drawn
    int size = vertices.size();
    for (int i = 0; i < size; i++) {
        if (i % 3 == 0) {
            glColor3f(((float) (rand() % 100) / 100.0), ((float) (rand() % 100) / 100.0),
                      ((float) (rand() % 100) / 100.0));
        }
        glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
    }

    glEnd();
    */
    render(scene);

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

void returnError(string error) {
    cout << "Error:\n" << error << endl;
    //exit(0);
}


void menu() {
    cout << "#--------** MENU **---------#" << endl;
    cout << "|    Modo de utilização:    |" << endl;
    cout << "|    ./engine {file.xml}    |" << endl;
    cout << "|---------------------------|" << endl;
    cout << "|          Teclas:          |" << endl;
    cout << "|   Mover câmera: W A S D   |" << endl;
    cout << "|  Zoom in : Up_arrow_key   |" << endl;
    cout << "| Zoom out : Down_arrow_key |" << endl;
    cout << "|     ativar GL_Point : P   |" << endl;
    cout << "|     ativar GL_Line : L    |" << endl;
    cout << "|     ativar GL_Fill : F    |" << endl;
    cout << "|---------------------------|" << endl;
    cout << "|  nota: .xml tem de estar  |" << endl;
    cout << "|   na pasta \"/src/Files/\"  |" << endl;
    cout << "#---------------------------#" << endl;

}

int main(int argc, char **argv) {

    if (argc != 2 || !regex_match(argv[1], regex("([a-zA-Z0-9\-_])+\.xml"))) {
        cout << "Argumentos inválidos" << endl;
        menu();
        //exit(0);
        return 0;
    }
    if (!readXML(argv[1], scene)) {
        cout << "Ficheiro Inválido ou Mal escrito\nCertificar que o ficheiro se encontra em /src/Files/" << endl;
        menu();
        //exit(0);
        return 0;
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
