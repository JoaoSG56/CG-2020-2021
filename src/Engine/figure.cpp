#include "../headers/figure.h"

using std::vector;

Figure::Figure()= default;

void Figure::setUp(std::vector<Point*> vertexes){
    buffer_size = vertexes.size();

    float* arr_vert = (float*) malloc(sizeof(float) * buffer_size * 3);

    int j,i;
    for(i=0,j=0;j < buffer_size;j++){
        arr_vert[i] = vertexes[j]->getX();
        arr_vert[i+1] = vertexes[j]->getY();
        arr_vert[i+2] = vertexes[j]->getZ();
        i+=3;
    }

    glGenBuffers(1,buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * buffer_size * 3, arr_vert, GL_STATIC_DRAW);

    free(arr_vert);
}

void Figure::draw() {

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawArrays(GL_TRIANGLES,0,buffer_size);

}