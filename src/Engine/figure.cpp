#include "../headers/figure.h"
using std::vector;

Figure::Figure(){
}

void Figure::setUp(vector<Point*> vertexes, vector<Point*> normal, vector<Point*> textureVec) {
    buffer_size[0] = vertexes.size();
    buffer_size[1] = normal.size();
    buffer_size[2] = textureVec.size();
    float* arr_vert = (float*) malloc(sizeof(float) * buffer_size[0] * 3);
    float* normal_vert = (float*) malloc(sizeof(float) * buffer_size[1] * 3);
    float* text_arr = (float*) malloc(sizeof(float) * buffer_size[2] * 2);
    int j, i;
    for (i = 0, j = 0; j < buffer_size[0]; j++) {
        arr_vert[i] = vertexes[j]->getX();
        arr_vert[i + 1] = vertexes[j]->getY();
        arr_vert[i + 2] = vertexes[j]->getZ();
        normal_vert[i] = normal[j]->getX();
        normal_vert[i + 1] = normal[j]->getY();
        normal_vert[i + 2] = normal[j]->getZ();
        i += 3;
    }
    for (i = 0, j = 0; j < buffer_size[2]; j++) {
        text_arr[i] = textureVec[j]->getX();
        text_arr[i + 1] = textureVec[j]->getY();
        i += 2;
    }


    glGenBuffers(1, &buffer1);
    glGenBuffers(1, &buffer2);
    glGenBuffers(1, &buffer3);

    glBindBuffer(GL_ARRAY_BUFFER, buffer1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[0] * 3, arr_vert, GL_STATIC_DRAW);
    // lights
    glBindBuffer(GL_ARRAY_BUFFER, buffer2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[1] * 3, normal_vert, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[2] * 2, text_arr, GL_STATIC_DRAW);

    free(arr_vert);
    free(normal_vert);
    free(text_arr);
}

void Figure::addMaterials(float diff[4], float spec[4], float emiss[4], float amb[4], float shine) {
    for (int i = 0; i < 4; i++) {
        diffuse[i] = diff[i];
        specular[i] = spec[i];
        emissive[i] = emiss[i];
        ambient[i] = amb[i];
    }
    shin = shine;
}

void Figure::loadTexture(string file) {

    unsigned int t, tw, th;
    unsigned char* texData;


    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    printf("%s\n",file.c_str());
    ilLoadImage((ILstring) file.c_str());

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            tw,
            th,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            texData);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Figure::draw() {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shin);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    glBindBuffer(GL_ARRAY_BUFFER, buffer1);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    if (buffer_size[1]) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer2);
        glNormalPointer(GL_FLOAT, 0, 0);
    }
    if (buffer_size[2]) {

        glBindBuffer(GL_ARRAY_BUFFER, buffer3);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, buffer_size[0]);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

}