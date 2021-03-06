#include <cmath>
#include <cstring>

int main(int argc, char *argv[]) {
    float x, y, z;
    float radius, height;
    int slices,stacks, optional;

    if (argc == 3 && strcmp(argv[1], "plane") == 0) { // plano

    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box
        x = atof(argv[2]);
        y = atof(argv[3]);
        z = atof(argv[4]);

        optional = atoi(argv[5]); // else = -1


    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
    }
    return 1;
}