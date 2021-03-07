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
    printf("%d\n", 6);
    file << "6" << endl;
    printf("%f %f %f\n", -x, y, -z);
    file << -x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, z);
    file << -x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, y, z);
    file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, y, z);
    file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, y, -z);
    file << x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, -z);
    file << -x << " " << y << " " << -z << endl;


    file.close();

}


void box(float a, float b, float c, int optional, string nome) {
    ofstream file("../src/Files/" + nome);
    float x, y, z;

    x = a / 2;
    y = b / 2;
    z = c / 2;


    if (optional == -1) { // não foi dada

    }
    printf("%d\n", 36);
        file << "36" << endl;
    printf("%d\n", optional);
        file << optional << endl;

    // face XOZ-1
    printf("%f %f %f\n", x, -y, z);
        file << x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", -x, -y, -z);
        file << -x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", x, -y, -z);
        file << x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", x, -y, z);
        file << x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", -x, -y, z);
        file << -x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", -x, -y, -z);
        file << -x << " " << -y << " " << -z << endl;

    // face XOZ-2
    printf("%f %f %f\n", -x, y, -z);
        file << -x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", x, y, z);
        file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, y, -z);
        file << x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, z);
        file << -x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, y, z);
        file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", -x, y, -z);
        file << -x << " " << y << " " << -z << endl;

    // face XOY-1
    printf("%f %f %f\n", -x, y, z);
        file << -x << " " << y << " " << z << endl;
    printf("%f %f %f\n", -x, -y, z);
        file << -x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", x, -y, z);
        file << x << " " << -y << " " << z << endl;

    printf("%f %f %f\n", x, -y, z);
        file << x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", x, y, z);
        file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", -x, y, z);
        file << -x << " " << y << " " << z << endl;

    // face XOY-2
    printf("%f %f %f\n", -x, -y, -z);
        file << -x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, -z);
        file << -x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", x, -y, -z);
        file << x << " " << -y << " " << -z << endl;

    printf("%f %f %f\n", x, y, -z);
        file << x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", x, -y, -z);
        file << x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, -z);
        file << -x << " " << y << " " << -z << endl;


    // face YOZ-1
    printf("%f %f %f\n", x, y, z);
        file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", x, -y, z);
        file << x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", x, -y, -z);
        file << x << " " << -y << " " << -z << endl;

    printf("%f %f %f\n", x, -y, -z);
        file << x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", x, y, -z);
        file << x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", x, y, z);
        file << x << " " << y << " " << z << endl;


    // face YOZ-2
    printf("%f %f %f\n", -x, -y, z);
        file << x << " " << -y << " " << z << endl;
    printf("%f %f %f\n", -x, y, z);
        file << x << " " << y << " " << z << endl;
    printf("%f %f %f\n", -x, -y, -z);
        file << x << " " << -y << " " << -z << endl;

    printf("%f %f %f\n", -x, y, -z);
        file << x << " " << y << " " << -z << endl;
    printf("%f %f %f\n", -x, -y, -z);
        file << x << " " << -y << " " << -z << endl;
    printf("%f %f %f\n", -x, y, z);
        file << x << " " << y << " " << z << endl;

}

void insertXML(string file,string name){
    XMLDocument xmldoc;
    if(xmldoc.LoadFile(("../src/Files/"+file).c_str())){
        // criar
        XMLElement* psceneElement = xmldoc.NewElement("scene");
            XMLElement* pmodelElement = xmldoc.NewElement("model");
            pmodelElement->SetAttribute("file",name.c_str());
        psceneElement->LinkEndChild(pmodelElement);
        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile(("../src/Files/"+file).c_str());
    }
    else {
        XMLElement* psceneElement = xmldoc.FirstChildElement();

        XMLElement* pmodelElement2 = xmldoc.NewElement("model");
        pmodelElement2->SetAttribute("file",name.c_str());

        psceneElement->LinkEndChild(pmodelElement2);

        xmldoc.LinkEndChild(psceneElement);

        xmldoc.SaveFile(("../src/Files/"+file).c_str());
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
        insertXML(file,argv[3]);
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);
        insertXML(file,argv[5]);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box

        if (argc == 6) {
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), -1, argv[5]);
            insertXML(file,argv[5]);
        } else {
            optional = atoi(argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), optional, argv[6]);
            insertXML(file,argv[6]);
        }

    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
        insertXML(file,argv[6]);
    } else {
        printf("Argumentos insuficientes");
        return 1;
    }

    return 0;
}