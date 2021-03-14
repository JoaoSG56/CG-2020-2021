#include <regex>
#include "../headers/generator.h"

void plane(int lado, string nome) {
    ofstream file(PATH + nome);
    float x, y, z;
    y = 0;

    if ((lado % 2) == 0) { // se for par
        x = (float) lado / 2;
        z = (float) lado / 2;
    } else {
        x = (float) lado / 2 + 0.5;
        z = (float) lado / 2 + 0.5;
    }

    //Vertices
    //printf("%d\n", 12);
    file << 12 << endl;
    file << -x << " " << y << " " << -z << endl;
    file << -x << " " << y << " " << z << endl;
    file << x << " " << y << " " << z << endl;

    file << x << " " << y << " " << z << endl;
    file << x << " " << y << " " << -z << endl;
    file << -x << " " << y << " " << -z << endl;

    file << -x << " " << y << " " << z << endl;
    file << -x << " " << y << " " << -z << endl;
    file << x << " " << y << " " << z << endl;

    file << x << " " << y << " " << -z << endl;
    file << x << " " << y << " " << z << endl;
    file << -x << " " << y << " " << -z << endl;


    file.close();

}


void box(float a, float b, float c, int optional, string nome) {
    ofstream file(PATH + nome);
    float x, y, z;

    x = a / 2;
    y = b / 2;
    z = c / 2;

    int divisoes = (optional == -1) ? 1 : optional;

    float moveX = a / divisoes;
    float moveY = b / divisoes;
    float moveZ = c / divisoes;


    //printf("%d\n", 36 * divisoes * divisoes);
    file << 36 * divisoes * divisoes << endl;


    for (int i = 0; i < divisoes; i++) {
        for (int j = 0; j < divisoes; j++) {
            // cima
            file << -x + (j * moveX) << " " << y << " " << -z + (i * moveZ) << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + i * moveZ << endl;

            file << -x + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << y << " " << -z + (i * moveZ) << endl;

            // baixo
            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + (i * moveZ) << endl;
            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + i * moveZ << endl;

            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + (i * moveZ) << endl;



            // frente
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + i * moveY << " " << z << endl;

            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + moveY + (i * moveY) << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << z << endl;


            // trás
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + i * moveY << " " << -z << endl;

            file << -x + (j * moveX) << " " << -y + moveY + (i * moveY) << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << -z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << -z << endl;

            // lado direito
            file << x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << x << " " << -y + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;

            file << x << " " << -y + moveY + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;

            // lado esquerdo
            file << -x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << -x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << -x << " " << -y + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;

            file << -x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << -x << " " << -y + moveY + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << -x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
        }
    }


}

void sphere(float radius, int slices, int stacks, string nome) {
    ofstream file(PATH + nome);
    float moveL = (2 * M_PI) / slices;
    float moveH = M_PI / stacks;
    float x1, x2, x3;
    float y1, y2, y3;
    float z1, z2, z3;

    file << 6 * slices * (stacks-2) + 6 * slices << endl;



    for (int i = 0; i < stacks / 2; i++) {
        for (int j = 0; j < slices; j++) {

            x1 = radius * cos(moveH * i) * sin(moveL * j);
            y1 = radius * sin(moveH * i);
            z1 = radius * cos(moveH * i) * cos(moveL * j);

            x2 = radius * cos(moveH * i) * sin(moveL + moveL * j);
            y2 = radius * sin(moveH * i);
            z2 = radius * cos(moveH * i) * cos(moveL + moveL * j);

            x3 = radius * cos(moveH + moveH * i) * sin(moveL * j);
            y3 = radius * sin(moveH + moveH * i);
            z3 = radius * cos(moveH + moveH * i) * cos(moveL * j);

            file << x1 << " " << y1 << " " << z1 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;
            file << x3 << " " << y3 << " " << z3 << endl;

            if (i != (stacks / 2) - 1) {
                file << x3 << " " << y3 << " " << z3 << endl;
                file << x2 << " " << y2 << " " << z2 << endl;

                file << radius * cos(moveH + moveH * i) * sin(moveL + moveL * j) << " "
                     << radius * sin(moveH + moveH * i) << " "
                     << radius * cos(moveH + moveH * i) * cos(moveL + moveL * j) << endl;
            }

            file << x2 << " " << -y2 << " " << z2 << endl;
            file << x1 << " " << -y1 << " " << z1 << endl;
            file << x3 << " " << -y3 << " " << z3 << endl;
            if (i != (stacks / 2) - 1) {
                file << x2 << " " << -y2 << " " << z2 << endl;
                file << x3 << " " << -y3 << " " << z3 << endl;

                file << radius * cos(moveH + moveH * i) * sin(moveL + moveL * j) << " "
                     << -(radius * sin(moveH + moveH * i)) << " "
                     << radius * cos(moveH + moveH * i) * cos(moveL + moveL * j) << endl;
            }
        }


    }
}

void cone(float radius, float height, int slices, int stacks, string nome) {
    ofstream file(PATH + nome);
    float alfa, x, z;
    float h = height;
    float l = sqrt(pow(h, 2) + pow(radius, 2)) / stacks;
    float t = radius / stacks;
    float dimSide = (2 * M_PI) / slices;
    file << 2 * slices * 3 + slices * 6 * (stacks - 1) << endl;
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            alfa = j * dimSide;
            if (i == 0) {
                file << 0 << " " << 0 << " " << 0 << endl;
                x = radius * sin(alfa + dimSide);
                z = radius * cos(alfa + dimSide);
                file << x << " " << 0 << " " << z << endl;

                x = radius * sin(alfa);
                z = radius * cos(alfa);
                file << x << " " << 0 << " " << z << endl;
            }
            if (i < stacks - 1) {
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                file << x << " " << (i + 1) * l << " " << z << endl;

                x = (radius - ((i + 1) * t)) * sin(alfa);
                z = (radius - ((i + 1) * t)) * cos(alfa);
                file << x << " " << (i + 1) * l << " " << z << endl;
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                file << x << " " << i * l << " " << z << endl;

                file << x << " " << i * l << " " << z << endl;
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);
                file << x << " " << i * l << " " << z << endl;
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                file << x << " " << (i + 1) * l << " " << z << endl;
            } else {
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                file << x << " " << i * l << " " << z << endl;
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);
                file << x << " " << i * l << " " << z << endl;
                file << 0 << " " << (i + 1) * l << " " << 0 << endl;
            }
        }
    }
}

void insertXML(string file, string name) {
    XMLDocument xmldoc;
    if (xmldoc.LoadFile((PATH + file).c_str())) {
        // criar
        XMLElement *psceneElement = xmldoc.NewElement("scene");
        XMLElement *pmodelElement = xmldoc.NewElement("model");
        pmodelElement->SetAttribute("file", name.c_str());
        psceneElement->LinkEndChild(pmodelElement);
        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile((PATH + file).c_str());
    } else {
        XMLElement *psceneElement = xmldoc.FirstChildElement();

        // verificar se já existe ficheiro

        for (XMLElement *paux = psceneElement->FirstChildElement(); paux; paux = paux->NextSiblingElement()) {
            //printf("%s\n", paux->Attribute("file"));
            if (paux->Attribute("file") == name)
                //printf("já existe\n");
                return;
        }

        XMLElement *pmodelElement2 = xmldoc.NewElement("model");
        pmodelElement2->SetAttribute("file", name.c_str());

        psceneElement->LinkEndChild(pmodelElement2);

        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile((PATH + file).c_str());
    }


}

void menu() {
    cout << "┌──────────────────────────** Menu **────────────────────────────┐ " << endl;
    cout << "│                                                                │" << endl;
    cout << "│      Usage: ./generator {COMANDO} {ARGUMENTS} {OUTPUT FILE}    │" << endl;
    cout << "├────────────────────────────────────────────────────────────────┤" << endl;
    cout << "│   COMANDO:                                                     │" << endl;
    cout << "│ - plane [SIZE]                                                 │" << endl;
    cout << "│    Cria um plano no plano XOZ, centrado na origem.             │" << endl;
    cout << "│                                                                │" << endl;
    cout << "│ - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISIONS]                   │" << endl;
    cout << "│    Cria uma box com as dimensões e divisões especificadas.     │" << endl;
    cout << "│                                                                │" << endl;
    cout << "│ - sphere [RADIUS] [SLICES] [STACKS]                            │" << endl;
    cout << "│    Cria uma esfera com o raio, numero de slices e stacks dadas.│" << endl;
    cout << "│                                                                │" << endl;
    cout << "│ - cone [RADIUS] [HEIGHT] [SLICES] [STACKS]                     │" << endl;
    cout << "│    Cria um cone com o raio, altura, slices e stacks dadas.     │" << endl;
    cout << "├────────────────────────────────────────────────────────────────┤" << endl;
    cout << "│   OUTPUT FILE:                                                 │" << endl;
    cout << "│    Ouput File tem de ser do formato 'Nome.3d'                  │" << endl;
    cout << "│  Corresponde ao ficheiro onde vão ser guardadas as coordenadas │" << endl;
    cout << "│          necessárias para serem lidas pela engine.             │" << endl;
    cout << "└────────────────────────────────────────────────────────────────┘" << endl;
}

void returnError(string error){
    cout << "Error:\n" << error << endl;
    exit(0);
}

int isFileValid(string fileName){
    return(regex_match(fileName,regex("([a-zA-Z0-9\-_])+\.3d")));
}

int main(int argc, char *argv[]) {

    float radius, height;
    int slices, stacks, optional;
    string name;

    if (argc == 1 || strcmp(argv[1], "menu") == 0) {
        menu();
        exit(0);
    } else if (argc == 4 && strcmp(argv[1], "plane") == 0) { // plano
        name = argv[3];
        if(!isFileValid(name))
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
        plane(atoi(argv[2]), name);
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        name = argv[5];
        if(!isFileValid(name))
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);
        sphere(radius, slices, stacks, name);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box

        if (argc == 6) {
            name = argv[5];
            if(!isFileValid(name))
                returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), -1, name);
        } else {
            name = argv[6];
            if(!isFileValid(name))
                returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            optional = atoi(argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), optional, name);
        }

    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        name = argv[6];
        if(!isFileValid(name))
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
        cone(radius, height, slices, stacks, name);
    } else {
        cout << "Argumentos insuficientes/inválidos" << endl;
        cout << "Para ajuda corra './generator'" << endl;
        exit(0);
    }
    cout << "Ficheiro guardado em " << PATH << name << endl;

    return 0;
}