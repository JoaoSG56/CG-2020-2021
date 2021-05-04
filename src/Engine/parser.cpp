
#include "../headers/parser.h"

using namespace tinyxml2;
using namespace std;

std::string XMLPath = "../src/Files/"; // for now
std::string figures3dPath = "../src/Files/"; // for now

int readfile(string ficheiro, Figure* f) {
    string delimiter = " ";
    ifstream inputFileStream(ficheiro);

    vector<Point*> points_list;

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

        Point* v = new Point(atof(a.c_str()), atof(b.c_str()), atof(c.c_str()));
        points_list.push_back(v);

    }

    f->setUp(points_list);

    inputFileStream.close();
    return 1;
}

void parseModels(XMLElement* element, Group* group) {

    for (element = element->FirstChildElement(); element; element = element->NextSiblingElement()) {
        string ficheiro = element->Attribute("file");
        if (!regex_match(ficheiro, regex("([a-zA-Z0-9\-_])+\.3d"))) {
            cout << "XML inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'\nnão carregado" << endl;
            return;
        }
        Figure* f = new Figure();
        if (!readfile(figures3dPath + ficheiro, f)) return;
        group->pushFigure(f);
        cout << "Ficheiro: " << ficheiro << " lido com sucesso " << endl;
    }

}

void parseTranslation(XMLElement* element, Group* group, vector<Translation*>* orbits) {
    float x = 0;
    float y = 0;
    float z = 0;
    float time = 0;

    element->QueryFloatAttribute("time", &time);
    element->QueryFloatAttribute("X", &x);
    element->QueryFloatAttribute("Y", &y);
    element->QueryFloatAttribute("Z", &z);


    Translation* t = new Translation(x, y, z, time);


    for (XMLElement* points = element->FirstChildElement(); points; points = points->NextSiblingElement()) {
        float px = 0, py = 0, pz = 0;

        points->QueryFloatAttribute("X", &px);
        points->QueryFloatAttribute("Y", &py);
        points->QueryFloatAttribute("Z", &pz);


        t->insertPoint(new Point(px, py, pz));
    }
    if (t->getCatSize() > 0) {
        t->constructCurve();
        orbits->push_back(t);
        // adicionar à orbita??
    }

    group->pushTransform(t);

}

void parseRotation(XMLElement* element, Group* group) {
    float x = 0;
    float y = 0;
    float z = 0;

    float angle = 0;
    float time = 0;

    element->QueryFloatAttribute("axisX", &x);
    element->QueryFloatAttribute("axisY", &y);
    element->QueryFloatAttribute("axisZ", &z);

    element->QueryFloatAttribute("time", &time);
    element->QueryFloatAttribute("angle", &angle);

    group->pushTransform(new Rotation(angle, x, y, z, time));

}

void parseScale(XMLElement* element, Group* group) {
    float x = 0;
    float y = 0;
    float z = 0;

    element->QueryFloatAttribute("X", &x);
    element->QueryFloatAttribute("Y", &y);
    element->QueryFloatAttribute("Z", &z);

    group->pushTransform(new Scale(x, y, z));

}

Type parseType(const char* type) {
    Type r = POINT;
    if (!strcmp(type, "POINT")) {
        r = POINT;
        printf("[DEBUG] 0\n");
    }
    else if (!strcmp(type, "DIRECTIONAL")) {
        r = DIRECTIONAL;
        printf("[DEBUG] 1\n");
    }
    else if (!strcmp(type, "SPOT")) {
        r = SPOT;
        printf("[DEBUG] 2\n");
    }
    printf("[DEBUG] END\n");
    return r;
}

void parseLights(XMLElement* element, Group* group) {
    printf("[DEBUG] entrou parseLights\n");

    Type type = POINT;
    float x=0,y=0,z=0;
    element = element->FirstChildElement();
    for (; element; element = element->NextSiblingElement()) {
        if (!strcmp(element->Name(), "light")) {
            if (element->Attribute("type"))
                type = parseType(element->Attribute("type"));
            element->QueryFloatAttribute("posX",&x);
            element->QueryFloatAttribute("posY",&y);
            element->QueryFloatAttribute("posZ",&z);
            printf("type: %u | x = %f | y = %f | z = %f\n",type,x,y,z);
            group->pushLight(new Light(type,new Point(x,y,z)));
        }
    }

}

void parseColour(XMLElement* element, Group* group) {
    float R = 1, G = 1, B = 1;

    element->QueryFloatAttribute("R", &R);
    element->QueryFloatAttribute("G", &G);
    element->QueryFloatAttribute("B", &B);

    group->setRGB(R, G, B);

}

void parseGroup(XMLElement* element, Group* group, vector<Translation*>* orbits) {
    XMLElement* current = element;

    if (!(strcmp(element->Name(), "translate"))) {
        parseTranslation(element, group, orbits);
    }

        //...
    else if (!(strcmp(element->Name(), "rotate"))) {
        parseRotation(element, group);
    } else if (!(strcmp(element->Name(), "scale"))) {
        parseScale(element, group);
    } else if (!(strcmp(element->Name(), "lights"))) {
        parseLights(element, group);
    } else if (!(strcmp(element->Name(), "models"))) {
        parseModels(element, group);
    } else if (!(strcmp(element->Name(), "group"))) {
        Group* child = new Group();

        group->pushGroup(child);

        element = element->FirstChildElement();

        parseGroup(element, child, orbits);
    } else if (!(strcmp(element->Name(), "colour"))) {
        parseColour(element, group);
    }
    current = current->NextSiblingElement();
    if (current) {
        parseGroup(current, group, orbits);
    }

}


int readXML(string file, Group* group, vector<Translation*>* orbits) {

    XMLDocument xmlDoc;
    XMLElement* element;

    if (!(xmlDoc.LoadFile((XMLPath + file).c_str()))) {
        element = xmlDoc.FirstChildElement("scene")->FirstChildElement(); // <group>

        parseGroup(element, group, orbits);

        return 1;
    } else {
        printf("ups\n");
    }
    return 0;

}


