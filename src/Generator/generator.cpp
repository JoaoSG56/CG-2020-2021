#include "headers/generator.h"

void plane(int lado, string nome) {
    ofstream file(nome);
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

void box_XOZ(float x, float y, float z, int optional){

}
void box_XOY(float x, float y, float z, int optional){

}
void box_YOZ(float x, float y, float z, int optional){

}

void box(float a, float b, float c, int optional, string nome) {
    ofstream file("../Figures/" + nome);
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

void menu() {

}

int main(int argc, char *argv[]) {
    float x, y, z;
    float radius, height;
    int slices, stacks, optional;

    if (argc == 1 || strcmp(argv[1], "menu") == 0) {
        menu();
    } else if (argc == 4 && strcmp(argv[1], "plane") == 0) { // plano
        plane(atoi(argv[2]), argv[3]);
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box

        if (argc == 6) {
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), -1, argv[5]);
        } else {
            optional = atoi(argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), optional, argv[6]);
        }

    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
    } else printf("Argumentos insuficientes");
    return 1;
}