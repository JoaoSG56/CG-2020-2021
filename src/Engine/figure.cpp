#include "../headers/figure.h"

using std::vector;

Figure::Figure()= default;

void Figure::setUp(std::vector<Point*> vertexes, std::vector<Point*> normal){
    buffer_size[0] = vertexes.size();
    buffer_size[1] = normal.size();
    float* arr_vert = (float*) malloc(sizeof(float) * buffer_size[0] * 3);
    float* normal_vert = (float*) malloc(sizeof(float) * buffer_size[1] * 3);
    int j,i;
    for(i=0,j=0;j < buffer_size[0];j++){
        arr_vert[i] = vertexes[j]->getX();
        arr_vert[i+1] = vertexes[j]->getY();
        arr_vert[i+2] = vertexes[j]->getZ();
        normal_vert[i] = normal[j]->getX();
        normal_vert[i+1] = normal[j]->getY();
        normal_vert[i+2] = normal[j]->getZ();
        i+=3;
    }


    glGenBuffers(1,buffers);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * buffer_size[0] * 3, arr_vert, GL_STATIC_DRAW);
    // lights
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * buffer_size[1] * 3, normal_vert,GL_STATIC_DRAW);

    free(arr_vert);
    free(normal_vert);
}

void Figure::draw() {

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);

    if(buffer_size[1]){
        glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
        glNormalPointer(GL_FLOAT,0,0);
    }

    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES,0,buffer_size[0]);
    glDisable(GL_LIGHTING);

}