#include <stdlib.h>
#include"../headers/figure.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#define OS_Windows 1
#endif

#define _USE_MATH_DEFINES


#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "../headers/point.h"
#include <regex>
#include "../headers/group.h"
#include "../headers/parser.h"
#include "../headers/camera.h"

#define ESCAPE 27

using namespace tinyxml2;
using namespace std;


GLenum mode = GL_LINE;

int window;
int menu_id;
bool fps_cam = false;
int camOption = 0; // 0 - static, 1 - fps
bool show_orbits = true;

vector<Translation*> orbits;

int timebase = 0, frame = 0;

CameraFPS* camera = new CameraFPS();
Camera* cameras[2];

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

void displayFPS() {
    int time;
    char title[25];

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        float fps = frame * 1000.0/(time - timebase);
        timebase = time;
        frame = 0;
        sprintf(title,"Engine  |  %.2f FPS",fps);
        glutSetWindowTitle(title);
    }
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
    for (int i = 0; i < tranformations.size(); i++)
        tranformations[i]->execute();
   // float R = 1, G = 1, B = 1;
    float R = group->getR()/255;
    float G = group->getG()/255;
    float B = group->getB()/255;

    glColor3f(R,G,B);
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    vector<Figure*> figures = group->getFigures();
    for(int i = 0; i< figures.size();i++)
        figures[i]->draw();


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
    //if(fps_cam) {
        Point *focus = cameras[camOption]->getFocus();
        Point* position = cameras[camOption]->getPosition();
        gluLookAt(position->getX(), position->getY(), position->getZ(),
                  focus->getX(), focus->getY(), focus->getZ(),
                  0.0f, 1.0f, 0.0f);
    //}
    /*
    else{
        Point *pos = camera->getStaticPosition();
        gluLookAt(pos->getX(), pos->getY(), pos->getZ(),
                  0,0,0,
                  0,1,0);
    }
     */
    eixos();

    render(scene);
    if(show_orbits)
        for(int i =0;i<orbits.size();i++)
            orbits[i]->drawCurve();

    displayFPS();

    // End of frame
    glutSwapBuffers();
}

void keyboardspecial(int key_code, int x, int y) {
    /*   switch (key_code) {
           case GLUT_KEY_UP:
               raioCamera -= 1;
               break;
           case GLUT_KEY_DOWN:
               raioCamera += 1;
               break;

           case GLUT_KEY_UP:
               camera->moveFoward();
               break;
           case GLUT_KEY_DOWN:
               camera->moveBackwards();
               break;
           case GLUT_KEY_LEFT:
               camera->moveLeft();
               break;
           case GLUT_KEY_RIGHT:
               camera->moveRight();
               break;
       }*/
    cameras[camOption]->specialKey(key_code);
    glutPostRedisplay();
}

// write function to process keyboard events
void keyboardfunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
            mode = GL_POINT;
            break;
        case 'l':
            mode = GL_LINE;
            break;
        case 'f':
            mode = GL_FILL;
            break;
        case 'o':
            show_orbits = !show_orbits;
            break;
        case ESCAPE:
            glutDestroyWindow(window);
            exit(0);
        default:
            cameras[camOption]->move(key);
            break;
    }
    glutPostRedisplay();
}
void moveMouse(int x, int y ){
    if(!fps_cam) return;


    float centerX = glutGet(GLUT_WINDOW_WIDTH)/2;
    float centerY = glutGet(GLUT_WINDOW_HEIGHT)/2;

    float dx = x - centerX;
    float dy = y - centerY;

    cameras[camOption]->turn(dx,dy);

    glutWarpPointer(centerX,centerY);
    glutPostRedisplay();

}

void returnError(string error) {
    cout << "Error:\n" << error << endl;
    //exit(0);
}

void menuChoice(int num){
    switch (num) {
        case 1:
            fps_cam = true;
            camOption = 1;
            break;
        case 0:
            fps_cam = false;
            camOption = 0;
            break;
        case -1:
            glutDestroyWindow(window);
            //exit(0);
    }
}

void createMenu(){
    menu_id = glutCreateMenu(menuChoice);
    glutAddMenuEntry("FPS Camera",1);
    glutAddMenuEntry("Static Camera",0);
    glutAddMenuEntry("Quit",-1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void menu() {
    cout << "#-------------** MENU **--------------#" << endl;
    cout << "|         Modo de utilização:         |" << endl;
    cout << "|         ./engine {file.xml}         |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|               Teclas:               |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|         Mudar Entre Câmeras:        |" << endl;
    cout << "|          Right Mouse Button         |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|           Modo Estático:            |" << endl;
    cout << "|      Mover câmera: W A S D UA DA    |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|         Modo First Person:          |" << endl;
    cout << "|  Mover câmera: Mouse + UA DA LA RA  |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|       Zoom in : Up_arrow_key        |" << endl;
    cout << "|      Zoom out : Down_arrow_key      |" << endl;
    cout << "|          ativar GL_Point : P        |" << endl;
    cout << "|          ativar GL_Line : L         |" << endl;
    cout << "|          ativar GL_Fill : F         |" << endl;
    cout << "|      Ativar/Desativar Órbitas: O    |" << endl;
    cout << "|-------------------------------------|" << endl;
    cout << "|       nota: .xml tem de estar       |" << endl;
    cout << "|        na pasta \"/src/Files/\"       |" << endl;
    cout << "|        nota2: UA -> Up Arrow        |" << endl;
    cout << "|       nota2': DA -> Down Arrow      |" << endl;
    cout << "|      nota2'': LA -> Left Arrow      |" << endl;
    cout << "|     nota2''': RA -> Right Arrow     |" << endl;
    cout << "#-------------------------------------#" << endl;

}

int main(int argc, char **argv) {

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    window = glutCreateWindow("CG@2020-2021");

#ifndef __APPLE__
    glewInit();
#endif


    glEnableClientState(GL_VERTEX_ARRAY);
    cameras[0] = new CameraStatic();
    cameras[1] = new CameraFPS();
    if (argc != 2 || !regex_match(argv[1], regex("([a-zA-Z0-9\-_])+\.xml"))) {
        menu();
        cout << "Argumentos inválidos" << endl;
        //exit(0);
        return 0;
    }
    if (!readXML(argv[1], scene,&orbits)) {
        menu();
        cout << "Ficheiro Inválido ou Mal escrito\nCertificar que o ficheiro se encontra em /src/Files/" << endl;
        //exit(0);
        return 0;
    }



// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutKeyboardFunc(keyboardfunc);
    glutSpecialFunc(keyboardspecial);
    glutPassiveMotionFunc(moveMouse);


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    createMenu();

    glutSetCursor(GLUT_CURSOR_NONE);
    float centerX = glutGet(GLUT_WINDOW_WIDTH)/2;
    float centerY = glutGet(GLUT_WINDOW_HEIGHT)/2;
    glutWarpPointer(centerX,centerY);
// enter GLUT's main cycle
    glutMainLoop();


    return 0;
}
