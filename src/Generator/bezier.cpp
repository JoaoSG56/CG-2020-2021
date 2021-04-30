
#include "../headers/bezier.h"

int bezierParser(string file) {

    string filePath = "../src/Files/" + file;

    string line;
    int* patches;
    float* controls;
    int n_patches;
    int n_controls;
    ifstream inputFileStream(filePath);

    if (!inputFileStream.is_open()) {
        cout << "error opening patch file" << endl;
        return 0;
    }

    inputFileStream >> n_patches;
    inputFileStream.ignore(1, '\n');
    patches = (int*) malloc(sizeof(int) * n_patches * 16);

    for (int i = 0; i < n_patches; i++) {
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a;
        for (int k = 0; k < 16; k++) {
            getline(lineStream, a, ',');
            patches[i * 16 + k] = stoi(a);
            //printf("%d - ",patches[i*16+k]);
        }
        //printf("\n");

    }
    inputFileStream >> n_controls;
    inputFileStream.ignore(1, '\n');
    controls = (float*) malloc(sizeof(float) * n_controls * 3);

    for (int i = 0; i < n_controls; i++) {
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a;
        for (int k = 0; k < 3; k++) {
            getline(lineStream, a, ',');
            controls[i * 3 + k] = stof(a);
            //printf("%f - ",controls[i*3+k]);
        }
        //printf("\n");
    }


}