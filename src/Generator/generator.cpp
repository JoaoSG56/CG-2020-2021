#include "../headers/generator.h"
#define GL_SILENCE_DEPRECATION

void writeToFile(vector<Point*> vertexes, vector<Point*> normal, string name) {
    ofstream file(PATH + name);
    file << vertexes.size() << endl;
    printf("[DEBUG] vertices size: %d\n", vertexes.size());
    for (int i = 0; i < vertexes.size();i++) {
        file << vertexes[i]->getX() << " " << vertexes[i]->getY() << " " << vertexes[i]->getZ() << endl;
    }

    printf("[DEBUG] normal size: %d\n", normal.size());
    for (int i = 0; i < normal.size();i++) {
        file << normal[i]->getX() << " " << normal[i]->getY() << " " << normal[i]->getZ() << endl;
    }

    file.close();
}


void torus(float distance, float radius, int slices , int stacks, string nome) {
    //ofstream file(PATH + nome);


    float theta = 0;
    float phi = 0;
    float theta_shift = (2*M_PI)/slices;
    float phi_shift = (2*M_PI)/stacks;
    vector<Point*> vertexes, normal;

    //file << slices*stacks*6 << endl;
    for(int i = 0; i < slices; i++){
        double a0 = i * theta_shift;
        double a1 = a0 + theta_shift;

        float x0 = cos(a0);
        float y0 = sin(a0);
        float x1 = cos(a1);
        float y1 = sin(a1);
        for(int j = 0; j < stacks; j++){

            vertexes.push_back(new Point(cos(theta) * (distance + radius * cos(phi)), sin(theta) * (distance + radius * cos(phi)), radius * sin(phi)));
            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi)) , sin(theta + theta_shift) * (distance + radius * cos(phi)), radius * sin(phi)));
            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)) , sin(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)) , radius * sin(phi + phi_shift)));

            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)) , sin(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)) ,radius * sin(phi + phi_shift)));
            vertexes.push_back(new Point(cos(theta) * (distance + radius * cos(phi + phi_shift)) ,sin(theta) * (distance + radius * cos(phi + phi_shift)) , radius * sin(phi + phi_shift)));
            vertexes.push_back(new Point(cos(theta) * (distance + radius * cos(phi)) , sin(theta) * (distance + radius * cos(phi)), radius * sin(phi)));


            normal.push_back(new Point(x0 * cos(j * phi_shift), y0 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(new Point(x1 * cos(j * phi_shift), y1 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(new Point(x0 * cos((j + 1) * phi_shift), y0 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));


            normal.push_back(new Point(x0 * cos((j + 1) * phi_shift), y0 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));
            normal.push_back(new Point(x1 * cos(j * phi_shift), y1 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(new Point(x1 * cos((j + 1) * phi_shift), y1 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));


            /*
            file << cos(theta)*(distance + radius * cos(phi))<< " " << sin(theta)*(distance + radius * cos(phi)) << " " << radius*sin(phi) << endl;
            file << cos(theta + theta_shift)*(distance + radius * cos(phi))<< " " << sin(theta + theta_shift)*(distance + radius * cos(phi)) << " " << radius*sin(phi) << endl;
            file << cos(theta + theta_shift)*(distance + radius * cos(phi + phi_shift))<< " " << sin(theta+theta_shift)*(distance + radius * cos(phi+phi_shift)) << " " << radius*sin(phi+phi_shift) << endl;



            file << cos(theta + theta_shift)*(distance + radius * cos(phi + phi_shift)) << " " << sin(theta+theta_shift)*(distance + radius * cos(phi+phi_shift)) << " " << radius*sin(phi+phi_shift) << endl;
            file << cos(theta)*(distance + radius * cos(phi + phi_shift)) << " " << sin(theta)*(distance + radius * cos(phi + phi_shift)) << " " <<radius*sin(phi + phi_shift) << endl;
            file << cos(theta)*(distance + radius * cos(phi)) << " " << sin(theta)*(distance + radius * cos(phi)) << " " << radius*sin(phi) << endl;
            */
            phi = phi_shift * (j + 1);
        }
        theta = theta_shift * (i + 1);
    }
    writeToFile(vertexes, normal, nome);
//torus 5 3 20 20 torus.3d

}


void plane(int lado, string nome) {
    //ofstream file(PATH + nome);
    float x, y, z;
    y = 0;
    vector<Point*> vertexes, normal;
    if ((lado % 2) == 0) { // se for par
        x = (float) lado / 2;
        z = (float) lado / 2;
    } else {
        x = (float) lado / 2 + 0.5;
        z = (float) lado / 2 + 0.5;
    }

    vertexes.push_back(new Point(-x,y,-z));
    vertexes.push_back(new Point(-x,y,z));
    vertexes.push_back(new Point(x,y,z));

    vertexes.push_back(new Point(x,y,z));
    vertexes.push_back(new Point(x,y,-z));
    vertexes.push_back(new Point(-x,y,-z));

    vertexes.push_back(new Point(-x,y,z));
    vertexes.push_back(new Point(-x,y,-z));
    vertexes.push_back(new Point(x,y,z));

    vertexes.push_back(new Point(x,y,-z));
    vertexes.push_back(new Point(x,y,z));
    vertexes.push_back(new Point(-x,y,-z));


    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));

    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));

    normal.push_back(new Point(0, -1, 0));
    normal.push_back(new Point(0, -1, 0));
    normal.push_back(new Point(0, -1, 0));

    normal.push_back(new Point(0, -1, 0));
    normal.push_back(new Point(0, -1, 0));
    normal.push_back(new Point(0, -1, 0));

    writeToFile(vertexes, normal, nome);
    //Vertices
    //printf("%d\n", 12);
    /*
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
*/
}


void box(float a, float b, float c, int optional, string nome) {
    //ofstream file(PATH + nome);
    float x, y, z;

    x = a / 2;
    y = b / 2;
    z = c / 2;

    int divisoes = (optional == -1) ? 1 : optional;

    float moveX = a / divisoes;
    float moveY = b / divisoes;
    float moveZ = c / divisoes;
    vector<Point*> vertexes, normal;

    //printf("%d\n", 36 * divisoes * divisoes);
    //file << 36 * divisoes * divisoes << endl;


    for (int i = 0; i < divisoes; i++) {
        for (int j = 0; j < divisoes; j++) {
            // cima
            vertexes.push_back(new Point(-x + (j * moveX) , y , -z + (i * moveZ)));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , y , -z + i * moveZ));

            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            vertexes.push_back(new Point(-x + (j * moveX) , y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX) , y , -z + (i * moveZ)));

            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            /*
            file << -x + (j * moveX) << " " << y << " " << -z + (i * moveZ) << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + i * moveZ << endl;

            file << -x + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + moveX + (j * moveX) << " " << y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << y << " " << -z + (i * moveZ) << endl;
*/
            // baixo
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX) , -y , -z + (i * moveZ)));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y , -z + i * moveZ));

            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX) , -y , -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX) , -y , -z + (i * moveZ)));

            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            /*
            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + (i * moveZ) << endl;
            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + i * moveZ << endl;

            file << -x + moveX + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + moveZ + i * moveZ << endl;
            file << -x + (j * moveX) << " " << -y << " " << -z + (i * moveZ) << endl;
            */


            // frente
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + moveY + i * moveY , z));
            vertexes.push_back(new Point(-x + (j * moveX) , -y + (i * moveY) , z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + i * moveY , z));

            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + moveY + i * moveY , z));
            vertexes.push_back(new Point(-x + (j * moveX) , -y + moveY + (i * moveY) , z));
            vertexes.push_back(new Point(-x + (j * moveX) , -y + (i * moveY) , z));

            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

            /*
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + i * moveY << " " << z << endl;

            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + moveY + (i * moveY) << " " << z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << z << endl;
            */

            // trás
            vertexes.push_back(new Point(-x + (j * moveX) , -y + (i * moveY) , -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + moveY + i * moveY , -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + i * moveY , -z));

            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

            vertexes.push_back(new Point(-x + (j * moveX) , -y + moveY + (i * moveY) , -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX) , -y + moveY + i * moveY , -z));
            vertexes.push_back(new Point(-x + (j * moveX) , -y + (i * moveY) , -z));

            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

            /*
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + i * moveY << " " << -z << endl;

            file << -x + (j * moveX) << " " << -y + moveY + (i * moveY) << " " << -z << endl;
            file << -x + moveX + (j * moveX) << " " << -y + moveY + i * moveY << " " << -z << endl;
            file << -x + (j * moveX) << " " << -y + (i * moveY) << " " << -z << endl;
            */

            // lado direito
            vertexes.push_back(new Point(x , -y + (i * moveY) , -z + (j * moveZ)));
            vertexes.push_back(new Point(x , -y + moveY + i * moveY , -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(x , -y + i * moveY , -z + moveZ + (j * moveZ)));

            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

            vertexes.push_back(new Point(x , -y + moveY + (i * moveY) , -z + (j * moveZ)));
            vertexes.push_back(new Point(x , -y + moveY + i * moveY , -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(x , -y + (i * moveY) , -z + (j * moveZ)));

            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

            /*
            file << x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << x << " " << -y + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;

            file << x << " " << -y + moveY + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            */

            // lado esquerdo
            vertexes.push_back(new Point(-x , -y + moveY + i * moveY , -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(-x , -y + (i * moveY) , -z + (j * moveZ)));
            vertexes.push_back(new Point(-x , -y + i * moveY , -z + moveZ + (j * moveZ)));

            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

            vertexes.push_back(new Point(-x , -y + moveY + i * moveY , -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(-x , -y + moveY + (i * moveY) , -z + (j * moveZ)));
            vertexes.push_back(new Point(-x , -y + (i * moveY) , -z + (j * moveZ)));

            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

            /*
            file << -x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << -x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << -x << " " << -y + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;

            file << -x << " " << -y + moveY + i * moveY << " " << -z + moveZ + (j * moveZ) << endl;
            file << -x << " " << -y + moveY + (i * moveY) << " " << -z + (j * moveZ) << endl;
            file << -x << " " << -y + (i * moveY) << " " << -z + (j * moveZ) << endl;
            */
        }
    }
    writeToFile(vertexes, normal, nome);


}

void sphere(float radius, int slices, int stacks, string nome) {
    //ofstream file(PATH + nome);
    float moveL = (2 * M_PI) / slices;
    float moveH = M_PI / stacks;
    float x1, x2, x3;
    float y1, y2, y3;
    float z1, z2, z3;
    vector<Point*> vertexes, normal;

    //file << 6 * slices * (stacks - 2) + 6 * slices << endl;


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

            vertexes.push_back(new Point(x1 , y1 ,z1));
            vertexes.push_back(new Point(x2 , y2 , z2));
            vertexes.push_back(new Point(x3 , y3, z3));

            normal.push_back(Point::getNormal(new Point(x1, y1, z1)));
            normal.push_back(Point::getNormal(new Point(x2, y2, z2)));
            normal.push_back(Point::getNormal(new Point(x3, y3, z3)));

            /*
            file << x1 << " " << y1 << " " << z1 << endl;
            file << x2 << " " << y2 << " " << z2 << endl;
            file << x3 << " " << y3 << " " << z3 << endl;
            */

            if (i != (stacks / 2) - 1) {
                vertexes.push_back(new Point(x3 , y3 , z3));
                vertexes.push_back(new Point(x2 , y2 ,z2));
                vertexes.push_back(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                        radius * sin(moveH + moveH * i),
                        radius * cos(moveH + moveH * i) * cos(moveL + moveL * j)));

                normal.push_back(Point::getNormal(new Point(x3, y3, z3)));
                normal.push_back(Point::getNormal(new Point(x2, y2, z2)));
                normal.push_back(Point::getNormal(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                    radius * sin(moveH + moveH * i),
                    radius * cos(moveH + moveH * i) * cos(moveL + moveL * j))));

                /*
                file << x3 << " " << y3 << " " << z3 << endl;
                file << x2 << " " << y2 << " " << z2 << endl;

                file << radius * cos(moveH + moveH * i) * sin(moveL + moveL * j) << " "
                     << radius * sin(moveH + moveH * i) << " "
                     << radius * cos(moveH + moveH * i) * cos(moveL + moveL * j) << endl;
                */
            }
            vertexes.push_back(new Point(x2,-y2,z2));
            vertexes.push_back(new Point(x1,-y1,z1));
            vertexes.push_back(new Point(x3,-y3,z3));

            normal.push_back(Point::getNormal(new Point(x2, -y2, z2)));
            normal.push_back(Point::getNormal(new Point(x1, -y1, z1)));
            normal.push_back(Point::getNormal(new Point(x3, -y3, z3)));

            /*
            file << x2 << " " << -y2 << " " << z2 << endl;
            file << x1 << " " << -y1 << " " << z1 << endl;
            file << x3 << " " << -y3 << " " << z3 << endl;
            */
            if (i != (stacks / 2) - 1) {
                vertexes.push_back(new Point(x2 , -y2, z2));
                vertexes.push_back(new Point(x3 , -y3 ,z3));
                vertexes.push_back(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j) ,
                        -(radius * sin(moveH + moveH * i)) ,
                        radius * cos(moveH + moveH * i) * cos(moveL + moveL * j)));

                normal.push_back(Point::getNormal(new Point(x2, -y2, z2)));
                normal.push_back(Point::getNormal(new Point(x3, -y3, z3)));
                normal.push_back(Point::getNormal(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                    -(radius * sin(moveH + moveH * i)),
                    radius * cos(moveH + moveH * i) * cos(moveL + moveL * j))));


                /*
                file << x2 << " " << -y2 << " " << z2 << endl;
                file << x3 << " " << -y3 << " " << z3 << endl;

                file << radius * cos(moveH + moveH * i) * sin(moveL + moveL * j) << " "
                     << -(radius * sin(moveH + moveH * i)) << " "
                     << radius * cos(moveH + moveH * i) * cos(moveL + moveL * j) << endl;
                     */
            }
        }

    }
    writeToFile(vertexes, normal, nome);
}

void cone(float radius, float height, int slices, int stacks, string nome) {
    //ofstream file(PATH + nome);
    float alfa, x, z;
    float h = height;
    float l = sqrt(pow(h, 2) + pow(radius, 2)) / stacks;
    float t = radius / stacks;
    float dimSide = (2 * M_PI) / slices;

    vector<Point*> vertexes, normal;
    
    //file << 2 * slices * 3 + slices * 6 * (stacks - 1) << endl;
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            alfa = j * dimSide;
            if (i == 0) {
                //file << 0 << " " << 0 << " " << 0 << endl;
                vertexes.push_back(new Point(0,0,0));
                x = radius * sin(alfa + dimSide);
                z = radius * cos(alfa + dimSide);
                //file << x << " " << 0 << " " << z << endl;
                vertexes.push_back(new Point(x,0,z));

                x = radius * sin(alfa);
                z = radius * cos(alfa);
                //file << x << " " << 0 << " " << z << endl;
                vertexes.push_back(new Point(x,0,z));

                normal.push_back(new Point());
                normal.push_back(new Point());
                normal.push_back(new Point());
            }
            if (i < stacks - 1) {
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                //file << x << " " << (i + 1) * l << " " << z << endl;
                vertexes.push_back(new Point(x , (i + 1) * l , z));

                x = (radius - ((i + 1) * t)) * sin(alfa);
                z = (radius - ((i + 1) * t)) * cos(alfa);
                //file << x << " " << (i + 1) * l << " " << z << endl;
                vertexes.push_back(new Point(x , (i + 1) * l , z));
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x , i * l , z));

                normal.push_back(new Point());
                normal.push_back(new Point());
                normal.push_back(new Point());

                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x , i * l , z));
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);
                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x , i * l, z));
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                //file << x << " " << (i + 1) * l << " " << z << endl;
                vertexes.push_back(new Point(x , (i + 1) * l , z));

                normal.push_back(new Point());
                normal.push_back(new Point());
                normal.push_back(new Point());
            } else {
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x , i * l , z));
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);
                //file << x << " " << i * l << " " << z << endl;
                //file << 0 << " " << (i + 1) * l << " " << 0 << endl;

                vertexes.push_back(new Point(x , i * l , z));
                vertexes.push_back(new Point(0 , (i + 1) * l , 0));

                normal.push_back(new Point());
                normal.push_back(new Point());
                normal.push_back(new Point());
            }
        }
    }
    writeToFile(vertexes, normal, nome);
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
    cout << "#--------------------------** Menu **----------------------------# " << endl;
    cout << "|                                                                |" << endl;
    cout << "|      Usage: ./generator {COMANDO} {ARGUMENTS} {OUTPUT FILE}    |" << endl;
    cout << "|----------------------------------------------------------------|" << endl;
    cout << "|   COMANDO:                                                     |" << endl;
    cout << "| - plane [SIZE]                                                 |" << endl;
    cout << "|    Cria um plano no plano XOZ, centrado na origem.             |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISIONS]                   |" << endl;
    cout << "|    Cria uma box com as dimensões e divisões especificadas.     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - sphere [RADIUS] [SLICES] [STACKS]                            |" << endl;
    cout << "|    Cria uma esfera com o raio, numero de slices e stacks dadas.|" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - cone [RADIUS] [HEIGHT] [SLICES] [STACKS]                     |" << endl;
    cout << "|    Cria um cone com o raio, altura, slices e stacks dadas.     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - torus [EXTERNAL RADIUS] [INTERNAL RADIUS] [SLICES] [STACKS]  |" << endl;
    cout << "|    Cria um torus no plano XOY, centrado na origem.             |" << endl;
    cout << "|                                                                |" << endl;
    cout << "| - patch [TESSELATION LEVEL] [INPUT FILE]                       |" << endl;
    cout << "|    Cria um tipo novo de figura com base nos patches de Bezier. |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|----------------------------------------------------------------|" << endl;
    cout << "|   OUTPUT FILE:                                                 |" << endl;
    cout << "|    Ouput File tem de ser do formato 'Nome.3d'                  |" << endl;
    cout << "|  Corresponde ao ficheiro onde vão ser guardadas as coordenadas |" << endl;
    cout << "|          necessárias para serem lidas pela engine.             |" << endl;
    cout << "#----------------------------------------------------------------#" << endl;
}

void returnError(string error) {
    cout << "Error:\n" << error << endl;
    //exit(0);
}

int isFileValid(string fileName) {
    return (regex_match(fileName, regex("([a-zA-Z0-9\-_])+\.3d")));
}

int main(int argc, char *argv[]) {
    if (OS_Windows) {
        system("mkdir ..\\src\\Files\\");
    } else
        system("mkdir -p ../src/Files/");
    float radius, height;
    int slices, stacks, optional;
    string name;
    if (argc == 1 || strcmp(argv[1], "menu") == 0) {
        menu();
        //exit(0);
        return 0;
    } else if (argc == 4 && strcmp(argv[1], "plane") == 0) { // plano
        name = argv[3];
        if (!isFileValid(name)) {
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            return 0;
        }
        plane(atoi(argv[2]), name);
    } else if (argc == 6 && strcmp(argv[1], "sphere") == 0) { // esfera
        name = argv[5];
        if (!isFileValid(name)) {
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            return 0;
        }
        radius = atof(argv[2]);
        slices = atoi(argv[3]);
        stacks = atoi(argv[4]);
        sphere(radius, slices, stacks, name);


    } else if ((argc == 6 || argc == 7) && strcmp(argv[1], "box") == 0) { // box

        if (argc == 6) {
            name = argv[5];
            if (!isFileValid(name)) {
                returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
                return 0;
            }
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), -1, name);
        } else {
            name = argv[6];
            if (!isFileValid(name)) {
                returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
                return 0;
            }
            optional = atoi(argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[4]), optional, name);
        }
    } else if (argc == 7 && strcmp(argv[1], "torus") == 0) {
        name = argv[6];
        if (!isFileValid(name)) {
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            return 0;
        }
        torus(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), name);

    } else if (argc == 7 && strcmp(argv[1], "cone") == 0) { // cone
        name = argv[6];
        if (!isFileValid(name)) {
            returnError("Nome de ficheiro inválido\nFicheiro tem de ser do formato: 'Nomedoficheiro.3d'");
            return 0;
        }
        radius = atof(argv[2]);
        height = atof(argv[3]);
        slices = atoi(argv[4]);
        stacks = atoi(argv[5]);
        cone(radius, height, slices, stacks, name);
    } else if (argc == 5 && strcmp(argv[1],"patch") == 0){
        bezierParser(stoi(argv[2]),argv[3],argv[4]);

    } else {
        cout << "Argumentos insuficientes/inválidos" << endl;
        cout << "Para ajuda corra './generator'" << endl;
        //exit(0);
        return 0;
    }
    cout << "Ficheiro guardado em " << PATH << name << endl;

    return 0;
}