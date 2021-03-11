#include "../headers/generator.h"

void plane(int lado, string nome) {
    ofstream file("../src/Files/" + nome);
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
    printf("%d\n", 12);
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
    ofstream file("../src/Files/" + nome);
    float x, y, z;

    x = a / 2;
    y = b / 2;
    z = c / 2;

    int divisoes = (optional == -1) ? 1 : optional;

    float moveX = a / divisoes;
    float moveY = b / divisoes;
    float moveZ = c / divisoes;


    printf("%d\n", 36 * divisoes * divisoes);
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
    ofstream file("../src/Files/" + nome);
    float shiftL = (2 * M_PI) / slices;
    float shiftH = (2 * M_PI) / (stacks * 2);
    float x1, x2, x3;
    float y1, y2, y3;
    float z1, z2, z3;

    printf("%d\n", 6 * slices * stacks * 2);
    file << 6 * slices * stacks * 2 << endl;

    for (int i = 0; i < stacks * 2; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = radius * cos(shiftH * i) * sin(shiftL * j);
            y1 = radius * sin(shiftH * i);
            z1 = radius * cos(shiftH * i) * cos(shiftL * j);

            x2 = radius * cos(shiftH * i) * sin(shiftL + shiftL * j);
            y2 = radius * sin(shiftH * i);
            z2 = radius * cos(shiftH * i) * cos(shiftL + shiftL * j);

            x3 = radius * cos(shiftH + shiftH * i) * sin(shiftL * j);
            y3 = radius * sin(shiftH + shiftH * i);
            z3 = radius * cos(shiftH + shiftH * i) * cos(shiftL * j);

            file << x1 << " " << y1 << " " << z1 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;
            file << x3 << " " << y3 << " " << z3 << endl;

            file << x3 << " " << y3 << " " << z3 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;

            file << radius * cos(shiftH + shiftH * i) * sin(shiftL + shiftL * j) << " "
                 << radius * sin(shiftH + shiftH * i) << " "
                 << radius * cos(shiftH + shiftH * i) * cos(shiftL + shiftL * j) << endl;
        }
    }
}

void insertXML(string file, string name) {
    XMLDocument xmldoc;
    if (xmldoc.LoadFile(("../src/Files/" + file).c_str())) {
        // criar
        XMLElement *psceneElement = xmldoc.NewElement("scene");
        XMLElement *pmodelElement = xmldoc.NewElement("model");
        pmodelElement->SetAttribute("file", name.c_str());
        psceneElement->LinkEndChild(pmodelElement);
        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile(("../src/Files/" + file).c_str());
    } else {
        XMLElement *psceneElement = xmldoc.FirstChildElement();

        // verificar se já existe ficheiro

        for (XMLElement *paux = psceneElement->FirstChildElement(); paux; paux = paux->NextSiblingElement()) {
            printf("%s\n", paux->Attribute("file"));
            if (paux->Attribute("file") == name)
                printf("já existe\n");
            return;
        }

        XMLElement *pmodelElement2 = xmldoc.NewElement("model");
        pmodelElement2->SetAttribute("file", name.c_str());

        psceneElement->LinkEndChild(pmodelElement2);

        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile(("../src/Files/" + file).c_str());
    }


}

void menu() {
    cout << "#_____________________________ HELP _____________________________# " << endl;
    cout << "|                                                                |" << endl;
    cout << "|   Usage: ./generator {COMMAND} ... {OUTPUT FILE}               |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   COMMANDS:                                                    |" << endl;
    cout << "| - plane [SIZE]                                                 |" << endl;
    cout << "|      Creates a square in the XZ plane, centred in the origin.  |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISIONS]                   |" << endl;
    cout << "|      Creates a box with the dimensions and divisions specified.|" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - sphere [RADIUS] [SLICE] [STACK]                              |" << endl;
    cout << "|      Creates a sphere with the radius, number of slices and    |" << endl;
    cout << "|      stacks given.                                             |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - cone [RADIUS] [HEIGHT] [SLICE] [STACK]                       |" << endl;
    cout << "|      Creates a cone with the radius, height, number of slices  |" << endl;
    cout << "|      and stacks given.                                         |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   OUTPUT FILE:                                                 |" << endl;
    cout << "| In the file section you can specify any file in which you wish |" << endl;
    cout << "| to save the coordinates generated with the previous commands.  |" << endl;
    cout << "|                                                                |" << endl;
    cout << "#________________________________________________________________#" << endl;
}

int main(int argc, char *argv[]) {
    string file = "teste.xml";

    float x, y, z;
    float radius, height;
    int slices, stacks, optional;

    if (argc == 1 || strcmp(argv[1], "menu") == 0) {
        menu();
    } else if (argc == 4 && strcmp(argv[1], "plane") == 0) { // plano
        plane(atoi(argv[2]), argv[3]);
        insertXML(file, argv[3]);
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);
        sphere(radius,slices,stacks,argv[5]);
        insertXML(file, argv[5]);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box

        if (argc == 6) {
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), -1, argv[5]);
            insertXML(file, argv[5]);
        } else {
            optional = atoi(argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), optional, argv[6]);
            insertXML(file, argv[6]);
        }

    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
        insertXML(file, argv[6]);
    } else {
        printf("Argumentos insuficientes");
        return 1;
    }

    return 0;
}