
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

        Vertex *v = new Vertex(atof(a.c_str()), atof(b.c_str()), atof(c.c_str()));
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

void parseTranslation(XMLElement *element);

void parseGroup(XMLElement *element, Group *group) {
    XMLElement *current = element;

    if (!(strcmp(element->Name(), "translate")));

        //...
    else if (!(strcmp(element->Name(), "rotate")));

    else if (!(strcmp(element->Name(), "scale")));

    else if (!(strcmp(element->Name(), "models"))) {
        printf("found models\n");
        parseModels(element, group);
        printf("out\n");
    } else if (!(strcmp(element->Name(), "group"))) {
        printf("found group \n");
        Group *child = new Group();

        group->pushGroup(child);

        element = element->FirstChildElement();

        parseGroup(element, child);
    }
    current = current->NextSiblingElement();
    if (current) {
        printf("vai a outro\n");
        parseGroup(current, group);
    }
    printf("vai sair\n");

}


int readXML(string file, Group *group) {

    XMLDocument xmlDoc;
    XMLElement *element;

    if (!(xmlDoc.LoadFile((XMLPath + file).c_str()))) {
        element = xmlDoc.FirstChildElement("scene")->FirstChildElement(); // <group>

        parseGroup(element, group);



        vector<Figure*> fig = group->getFigures();
        for(int j = 0; j < fig.size(); j++){
            printf("\n\n\n%d\n",j);
            vector<Vertex*> vert = fig[j]->getVertexes();
            for(int i = 0; i < vert.size(); i++){
                printf("%f %f %f\n",vert[i]->getX(),vert[i]->getY(),vert[i]->getZ());
            }
        }

        return 1;
    } else {
        printf("ups\n");
    }
    return 0;

}


