
#include "../headers/parser.h"

using namespace tinyxml2;
using namespace std;

int readfile(string ficheiro, vector<Point> vertices) {
    string delimiter = " ";
    ifstream inputFileStream(ficheiro);
    if(!inputFileStream.is_open()){
        //returnError("Ficheiro '" + ficheiro + "' não encontrado");
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


        vertices.push_back(*new Point(atof(a.c_str()), atof(b.c_str()), atof(c.c_str())));

    }
    return 1;
}

int readXML(string file, vector<Point> vertices) {
    XMLDocument xmldoc;
    if (!(xmldoc.LoadFile((XMLPath + file).c_str()))) {
        XMLElement *pRootElement = xmldoc.FirstChildElement();

        for (XMLElement *element = pRootElement->FirstChildElement(); element; element = element->NextSiblingElement()) {
            string ficheiro = element->Attribute("file");
            if(!regex_match(ficheiro,regex("([a-zA-Z0-9\-_])+\.3d"))) {
                //returnError("XML inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'\n" + file +
                 //           " não carregado");
                return -1; // ajustar
            }

            if(!readfile(figures3dPath + ficheiro,vertices)) return 0;
            cout << "Ficheiro: " << ficheiro << " lido com sucesso " << endl;
        }
        return 1;
    } else {
        return 0;
    }

}
