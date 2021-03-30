
#include "../headers/parser.h"

using namespace tinyxml2;
using namespace std;

std::string XMLPath = "../src/Files/"; // for now
std::string figures3dPath = "../src/Files/"; // for now

int readfile(string ficheiro, Figure *f) {
    string delimiter = " ";
    ifstream inputFileStream(ficheiro);
    if (!inputFileStream.is_open()) {
        cout << "Ficheiro '" + ficheiro + "' não encontrado" << endl;
        return 0;
    }
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

        Point *v = new Point(atof(a.c_str()), atof(b.c_str()), atof(c.c_str()));
        f->pushVertex(v);

    }
    return 1;
}

void parseModels(XMLElement *element, Group *group) {

    for (element = element->FirstChildElement(); element; element = element->NextSiblingElement()) {
        string ficheiro = element->Attribute("file");
        if (!regex_match(ficheiro, regex("([a-zA-Z0-9\-_])+\.3d"))) {
            cout << "XML inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'\nnão carregado" << endl;
            return;
        }
        Figure *f = new Figure();
        if (!readfile(figures3dPath + ficheiro, f)) return;
        group->pushFigure(f);
        cout << "Ficheiro: " << ficheiro << " lido com sucesso " << endl;
    }

}

void parseTranslation(XMLElement *element, Group *group) {
    float x = 0;
    float y = 0;
    float z = 0;

    element->QueryFloatAttribute("X",&x);
    element->QueryFloatAttribute("Y",&y);
    element->QueryFloatAttribute("Z",&z);

    Translation* t = new Translation(x,y,z);
    group->pushTransform(t);

}

void parseRotation(XMLElement *element, Group *group) {
    float x = 0;
    float y = 0;
    float z = 0;

    float angle = 0;

    element->QueryFloatAttribute("axisX",&x);
    element->QueryFloatAttribute("axisY",&y);
    element->QueryFloatAttribute("axisZ",&z);

    element->QueryFloatAttribute("angle",&angle);

    Rotation* r = new Rotation(angle,x,y,z);
    group->pushTransform(r);

}

void parseScale(XMLElement *element, Group *group) {
    float x = 0;
    float y = 0;
    float z = 0;

    element->QueryFloatAttribute("X",&x);
    element->QueryFloatAttribute("Y",&y);
    element->QueryFloatAttribute("Z",&z);

    Scale* s = new Scale(x,y,z);
    group->pushTransform(s);

}

void parseColour(XMLElement* element, Group* group) {
    float R = 1, G = 1, B = 1;

    element->QueryFloatAttribute("R", &R);
    element->QueryFloatAttribute("G", &G);
    element->QueryFloatAttribute("B", &B);

    group->setRGB(R, G, B);

}

void parseGroup(XMLElement *element, Group *group) {
    XMLElement *current = element;

    if (!(strcmp(element->Name(), "translate"))) {
        parseTranslation(element, group);
    }

        //...
    else if (!(strcmp(element->Name(), "rotate"))){
        parseRotation(element, group);
    }

    else if (!(strcmp(element->Name(), "scale"))){
        parseScale(element, group);
    }

    else if (!(strcmp(element->Name(), "models"))) {
        parseModels(element, group);
    } 
    else if (!(strcmp(element->Name(), "group"))) {
        Group *child = new Group();

        group->pushGroup(child);

        element = element->FirstChildElement();

        parseGroup(element, child);
    }
    else if (!(strcmp(element->Name(), "colour"))) {
        parseColour(element,group);
    }
    current = current->NextSiblingElement();
    if (current) {
        parseGroup(current, group);
    }

}


int readXML(string file, Group *group) {

    XMLDocument xmlDoc;
    XMLElement *element;

    if (!(xmlDoc.LoadFile((XMLPath + file).c_str()))) {
        element = xmlDoc.FirstChildElement("scene")->FirstChildElement(); // <group>

        parseGroup(element, group);

        return 1;
    } else {
        printf("ups\n");
    }
    return 0;

}


