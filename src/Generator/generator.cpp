#include "../headers/generator.h"

#define GL_SILENCE_DEPRECATION

void writeToFile(vector<Point*> vertexes, vector<Point*> normal, vector<Point*> texture, string name) {
    ofstream file(PATH + name);
    file << vertexes.size() << endl;
    printf("[DEBUG] vertices size: %lu\n", vertexes.size());
    for (int i = 0; i < vertexes.size(); i++) {
        file << vertexes[i]->getX() << " " << vertexes[i]->getY() << " " << vertexes[i]->getZ() << endl;
    }

    printf("[DEBUG] normal size: %lu\n", normal.size());
    for (int i = 0; i < normal.size(); i++) {
        file << normal[i]->getX() << " " << normal[i]->getY() << " " << normal[i]->getZ() << endl;
    }
    printf("[DEBUG] texture size: %lu\n", texture.size());
    for (int i = 0; i < texture.size(); i++) {
        file << texture[i]->getX() << " " << texture[i]->getY() << endl;
    }

    file.close();
}


void torus(float distance, float radius, int slices, int stacks, string nome) {

    float theta = 0;
    float phi = 0;
    float theta_shift = (2 * M_PI) / slices;
    float phi_shift = (2 * M_PI) / stacks;
    vector<Point*> vertexes, normal, texture;

    float textureSide = float(1) / float(stacks);
    float textureRing = float(1) / float(slices);

    for (int i = 0; i < slices; i++) {
        double a0 = i * theta_shift;
        double a1 = a0 + theta_shift;

        float x0 = cos(a0);
        float y0 = sin(a0);
        float x1 = cos(a1);
        float y1 = sin(a1);
        for (int j = 0; j < stacks; j++) {

            vertexes.push_back(
                    new Point(cos(theta) * (distance + radius * cos(phi)), sin(theta) * (distance + radius * cos(phi)),
                              radius * sin(phi)));
            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi)),
                                         sin(theta + theta_shift) * (distance + radius * cos(phi)), radius * sin(phi)));
            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)),
                                         sin(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)),
                                         radius * sin(phi + phi_shift)));
            texture.push_back(new Point(i * textureRing, j * textureSide, 0));
            texture.push_back(new Point((i + 1) * textureRing, j * textureSide, 0));
            texture.push_back(new Point(i * textureRing, (j + 1) * textureSide, 0));


            vertexes.push_back(new Point(cos(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)),
                                         sin(theta + theta_shift) * (distance + radius * cos(phi + phi_shift)),
                                         radius * sin(phi + phi_shift)));
            vertexes.push_back(new Point(cos(theta) * (distance + radius * cos(phi + phi_shift)),
                                         sin(theta) * (distance + radius * cos(phi + phi_shift)),
                                         radius * sin(phi + phi_shift)));
            vertexes.push_back(
                    new Point(cos(theta) * (distance + radius * cos(phi)), sin(theta) * (distance + radius * cos(phi)),
                              radius * sin(phi)));

            texture.push_back(new Point(i * textureRing, (j + 1) * textureSide, 0));
            texture.push_back(new Point((i + 1) * textureRing, j * textureSide, 0));
            texture.push_back(new Point((i + 1) * textureRing, (j + 1) * textureSide, 0));


            normal.push_back(new Point(x0 * cos(j * phi_shift), y0 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(new Point(x1 * cos(j * phi_shift), y1 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(
                    new Point(x0 * cos((j + 1) * phi_shift), y0 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));


            normal.push_back(
                    new Point(x0 * cos((j + 1) * phi_shift), y0 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));
            normal.push_back(new Point(x1 * cos(j * phi_shift), y1 * cos(j * phi_shift), sin(j * phi_shift)));
            normal.push_back(
                    new Point(x1 * cos((j + 1) * phi_shift), y1 * cos((j + 1) * phi_shift), sin((j + 1) * phi_shift)));


            phi = phi_shift * (j + 1);
        }
        theta = theta_shift * (i + 1);
    }
    writeToFile(vertexes, normal, texture, nome);
//torus 5 3 20 20 torus.3d

}


void plane(int lado, string nome) {
    float x, y, z;
    y = 0;
    vector<Point*> vertexes, normal, texture;
    if ((lado % 2) == 0) { // se for par
        x = (float) lado / 2;
        z = (float) lado / 2;
    } else {
        x = (float) lado / 2 + 0.5;
        z = (float) lado / 2 + 0.5;
    }

    vertexes.push_back(new Point(-x, y, -z));
    vertexes.push_back(new Point(-x, y, z));
    vertexes.push_back(new Point(x, y, z));

    vertexes.push_back(new Point(x, y, z));
    vertexes.push_back(new Point(x, y, -z));
    vertexes.push_back(new Point(-x, y, -z));

    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));

    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));
    normal.push_back(new Point(0, 1, 0));

    texture.push_back(new Point(1, 1, 0));
    texture.push_back(new Point(1, 0, 0));
    texture.push_back(new Point(0, 1, 0));

    texture.push_back(new Point(0, 1, 0));
    texture.push_back(new Point(1, 0, 0));
    texture.push_back(new Point(0, 0, 0));

    writeToFile(vertexes, normal, texture, nome);

}


void box(float a, float b, float c, int optional, string nome) {
    float x, y, z;

    x = a / 2;
    y = b / 2;
    z = c / 2;

    int divisoes = (optional == -1) ? 1 : optional;

    float moveX = a / divisoes;
    float moveY = b / divisoes;
    float moveZ = c / divisoes;

    float textureY1 = c / (c * 2 + b);
    //float textureY2 = (c + b) / ((c * 2) + b);

    float textureX1 = c / ((c * 2) + (a * 2));
    //float textureX2 = (c + a) / ((c * 2) + (x * 2));
    float textureX3 = ((c * 2) + a) / ((c * 2) + (a * 2));

    float textShiftY = (c / ((c * 2) + b)) / float(optional);
    float textShiftX = (a / ((c * 2) + (a * 2))) / float(optional);
    float textShiftZ = (c / ((c * 2) + (a * 2))) / float(optional);

    vector<Point*> vertexes, normal, textures;


    for (int i = 0; i < divisoes; i++) {
        for (int j = 0; j < divisoes; j++) {
            // cima
            vertexes.push_back(new Point(-x + (j * moveX), y, -z + (i * moveZ)));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), y, -z + i * moveZ));

            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            textures.push_back(new Point(textureX1 + (j * textShiftX), 1 - (i * textShiftZ), 0));
            textures.push_back(new Point(textureX1 + (j * textShiftX), (1 - textShiftZ) - (i * textShiftZ), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), 1 - (i * textShiftZ), 0));


            vertexes.push_back(new Point(-x + (j * moveX), y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX), y, -z + (i * moveZ)));

            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));
            normal.push_back(new Point(0, 1, 0));

            textures.push_back(new Point(textureX1 + (j * textShiftX), (1 - textShiftZ) - (i * textShiftZ), 0));
            textures.push_back(
                    new Point((textureX1 + textShiftX) + (j * textShiftX), (1 - textShiftZ) - (i * textShiftZ), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), 1 - (i * textShiftZ), 0));

            // baixo
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX), -y, -z + (i * moveZ)));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y, -z + i * moveZ));

            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            textures.push_back(new Point(textureX1 + (j * textShiftX), (i * textShiftZ), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), (i * textShiftZ), 0));
            textures.push_back(new Point(textureX1 + (j * textShiftX), textShiftZ + (i * textShiftZ), 0));

            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX), -y, -z + moveZ + i * moveZ));
            vertexes.push_back(new Point(-x + (j * moveX), -y, -z + (i * moveZ)));

            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));
            normal.push_back(new Point(0, -1, 0));

            textures.push_back(new Point(textureX1 + (j * textShiftX), textShiftZ + (i * textShiftZ), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), (i * textShiftZ), 0));
            textures.push_back(
                    new Point((textureX1 + textShiftX) + (j * textShiftX), textShiftZ + (i * textShiftZ), 0));


            // frente
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + moveY + i * moveY, z));
            vertexes.push_back(new Point(-x + (j * moveX), -y + (i * moveY), z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + i * moveY, z));

            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

            textures.push_back(new Point(textureX1 + (j * textShiftX), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point(textureX1 + (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));

            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + moveY + i * moveY, z));
            vertexes.push_back(new Point(-x + (j * moveX), -y + moveY + (i * moveY), z));
            vertexes.push_back(new Point(-x + (j * moveX), -y + (i * moveY), z));

            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));
            normal.push_back(new Point(0, 0, 1));

            textures.push_back(new Point(textureX1 + (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(new Point((textureX1 + textShiftX) + (j * textShiftX), textureY1 + (i * textShiftY), 0));
            textures.push_back(
                    new Point((textureX1 + textShiftX) + (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY),
                              0));


            // trás
            vertexes.push_back(new Point(-x + (j * moveX), -y + (i * moveY), -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + moveY + i * moveY, -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + i * moveY, -z));

            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

            textures.push_back(new Point(1 - (j * textShiftX), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point(1 - (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(new Point((1 - textShiftX) - (j * textShiftX), textureY1 + (i * textShiftY), 0));

            vertexes.push_back(new Point(-x + (j * moveX), -y + moveY + (i * moveY), -z));
            vertexes.push_back(new Point(-x + moveX + (j * moveX), -y + moveY + i * moveY, -z));
            vertexes.push_back(new Point(-x + (j * moveX), -y + (i * moveY), -z));

            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));
            normal.push_back(new Point(0, 0, -1));

            textures.push_back(new Point(1 - (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(
                    new Point((1 - textShiftX) - (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(new Point((1 - textShiftX) - (j * textShiftX), textureY1 + (i * textShiftY), 0));


            // lado direito
            vertexes.push_back(new Point(x, -y + (i * moveY), -z + (j * moveZ)));
            vertexes.push_back(new Point(x, -y + moveY + i * moveY, -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(x, -y + i * moveY, -z + moveZ + (j * moveZ)));

            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

            textures.push_back(new Point(textureX3 - (j * textShiftZ), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point(textureX3 - (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(new Point((textureX3 - textShiftZ) - (j * textShiftZ), textureY1 + (i * textShiftY), 0));

            vertexes.push_back(new Point(x, -y + moveY + (i * moveY), -z + (j * moveZ)));
            vertexes.push_back(new Point(x, -y + moveY + i * moveY, -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(x, -y + (i * moveY), -z + (j * moveZ)));

            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));
            normal.push_back(new Point(1, 0, 0));

            textures.push_back(new Point(textureX3 - (j * textShiftZ), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(
                    new Point((textureX3 - textShiftZ) - (j * textShiftX), (textureY1 + textShiftY) + (i * textShiftY),
                              0));
            textures.push_back(new Point((textureX3 - textShiftZ) - (j * textShiftX), textureY1 + (i * textShiftY), 0));


            // lado esquerdo
            vertexes.push_back(new Point(-x, -y + moveY + i * moveY, -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(-x, -y + (i * moveY), -z + (j * moveZ)));
            vertexes.push_back(new Point(-x, -y + i * moveY, -z + moveZ + (j * moveZ)));

            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

            textures.push_back(new Point((j * textShiftZ), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point(textShiftZ + (j * textShiftZ), textureY1 + (i * textShiftY), 0));
            textures.push_back(new Point((j * textShiftZ), (textureY1 + textShiftY) + (i * textShiftY), 0));


            vertexes.push_back(new Point(-x, -y + moveY + i * moveY, -z + moveZ + (j * moveZ)));
            vertexes.push_back(new Point(-x, -y + moveY + (i * moveY), -z + (j * moveZ)));
            vertexes.push_back(new Point(-x, -y + (i * moveY), -z + (j * moveZ)));

            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));
            normal.push_back(new Point(-1, 0, 0));

            textures.push_back(new Point((j * textShiftZ), (textureY1 + textShiftY) + (i * textShiftY), 0));
            textures.push_back(new Point(textShiftZ + (j * textShiftZ), textureY1 + (i * textShiftY), 0));
            textures.push_back(
                    new Point(textShiftZ + (j * textShiftZ), (textureY1 + textShiftY) + (i * textShiftY), 0));


        }
    }
    writeToFile(vertexes, normal, textures, nome);


}

void sphere(float radius, int slices, int stacks, string nome) {
    float moveL = (2 * M_PI) / stacks;
    float moveH = M_PI / slices;
    float x1, x2, x3;
    float y1, y2, y3;
    float z1, z2, z3;
    vector<Point*> vertexes, normal, texture;

    float textureU = 1 / (float) (slices/2);
    float textureV = 1 / (float) stacks;

    for (int i = 0; i < slices / 2; i++) {
        for (int j = 0; j < stacks; j++) {

            x1 = radius * cos(moveH * i) * sin(moveL * j);
            y1 = radius * sin(moveH * i);
            z1 = radius * cos(moveH * i) * cos(moveL * j);

            x2 = radius * cos(moveH * i) * sin(moveL + moveL * j);
            y2 = radius * sin(moveH * i);
            z2 = radius * cos(moveH * i) * cos(moveL + moveL * j);

            x3 = radius * cos(moveH + moveH * i) * sin(moveL * j);
            y3 = radius * sin(moveH + moveH * i);
            z3 = radius * cos(moveH + moveH * i) * cos(moveL * j);

            vertexes.push_back(new Point(x1, y1, z1));
            vertexes.push_back(new Point(x2, y2, z2));
            vertexes.push_back(new Point(x3, y3, z3));

            normal.push_back(Point::getNormal(new Point(x1, y1, z1)));
            normal.push_back(Point::getNormal(new Point(x2, y2, z2)));
            normal.push_back(Point::getNormal(new Point(x3, y3, z3)));

            texture.push_back(new Point(textureV*j,(1+textureU*i)/2,0));
            texture.push_back(new Point(textureV*j+textureV,(1+textureU*i)/2,0));
            texture.push_back(new Point(textureV*j,(1+textureU*i+textureU)/2,0));


            if (i != (slices / 2) - 1) {
                vertexes.push_back(new Point(x3, y3, z3));
                vertexes.push_back(new Point(x2, y2, z2));
                vertexes.push_back(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                                             radius * sin(moveH + moveH * i),
                                             radius * cos(moveH + moveH * i) * cos(moveL + moveL * j)));

                normal.push_back(Point::getNormal(new Point(x3, y3, z3)));
                normal.push_back(Point::getNormal(new Point(x2, y2, z2)));
                normal.push_back(Point::getNormal(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                                                            radius * sin(moveH + moveH * i),
                                                            radius * cos(moveH + moveH * i) * cos(moveL + moveL * j))));

                texture.push_back(new Point(textureV*j,(1+textureU*i+textureU)/2,0));
                texture.push_back(new Point(textureV*j+textureV,(1+textureU*i)/2,0));
                texture.push_back(new Point(textureV*j+textureV,(1+textureU*i+textureU)/2,0));

            }
            vertexes.push_back(new Point(x2, -y2, z2));
            vertexes.push_back(new Point(x1, -y1, z1));
            vertexes.push_back(new Point(x3, -y3, z3));

            normal.push_back(Point::getNormal(new Point(x2, -y2, z2)));
            normal.push_back(Point::getNormal(new Point(x1, -y1, z1)));
            normal.push_back(Point::getNormal(new Point(x3, -y3, z3)));

            texture.push_back(new Point(textureV*j+textureV,(1+(-textureU*i))/2,0));
            texture.push_back(new Point(textureV*j,(1+(-textureU*i))/2,0));
            texture.push_back(new Point(textureV*j,(1+(-textureU*i-textureU))/2,0));

            if (i != (slices / 2) - 1) {
                vertexes.push_back(new Point(x2, -y2, z2));
                vertexes.push_back(new Point(x3, -y3, z3));
                vertexes.push_back(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                                             -(radius * sin(moveH + moveH * i)),
                                             radius * cos(moveH + moveH * i) * cos(moveL + moveL * j)));

                normal.push_back(Point::getNormal(new Point(x2, -y2, z2)));
                normal.push_back(Point::getNormal(new Point(x3, -y3, z3)));
                normal.push_back(Point::getNormal(new Point(radius * cos(moveH + moveH * i) * sin(moveL + moveL * j),
                                                            -(radius * sin(moveH + moveH * i)),
                                                            radius * cos(moveH + moveH * i) * cos(moveL + moveL * j))));

                texture.push_back(new Point(textureV*j+textureV,(1+(-textureU*i))/2,0));
                texture.push_back(new Point(textureV*j,(1+(-textureU*i-textureU))/2,0));
                texture.push_back(new Point(textureV*j+textureV,(1+(-textureU*i-textureU))/2,0));

            }
        }

    }
//

/*

    for (int i = 0; i < vertexes.size(); i += 3) {
        float x, y;

        x = (-atan2(vertexes[i]->getZ(), vertexes[i]->getX()) + M_PI) / (2 * M_PI);
        y = (1 - vertexes[i]->getY() / radius) / 2.0;

        x2 = (-atan2(vertexes[i + 1]->getZ(), vertexes[i + 1]->getX()) + M_PI) / (2 * M_PI);
        y2 = (1 - vertexes[i + 1]->getY() / radius) / 2.0;

        x3 = (-atan2(vertexes[i + 2]->getZ(), vertexes[i + 2]->getX()) + M_PI) / (2 * M_PI);
        y3 = (1 - vertexes[i + 2]->getY() / radius) / 2.0;


        if (x > x2 && fabs(x - x2) > 0.8)
            x2 = 1.0;
        if (x > x3 && fabs(x - x3) > 0.8)
            x3 = 1.0;
        if (x2 > x && fabs(x2 - x) > 0.8)
            x = 1.0;
        if (x2 > x3 && fabs(x2 - x3) > 0.8)
            x3 = 1.0;
        if (x3 > x && fabs(x3 - x) > 0.8)
            x = 1.0;
        if (x3 > x2 && fabs(x3 - x2) > 0.8)
            x2 = 1.0;

        texture.push_back(new Point(x, y, 0));
        texture.push_back(new Point(x2, y2, 0));
        texture.push_back(new Point(x3, y3, 0));
    }

    */



    writeToFile(vertexes, normal, texture, nome);
}

void cone(float radius, float height, int slices, int stacks, string nome) {
    //ofstream file(PATH + nome);
    float alfa, x, z;
    float h = height;
    float l = sqrt(pow(h, 2) + pow(radius, 2)) / stacks;
    float t = radius / stacks;
    float dimSide = (2 * M_PI) / slices;

    vector<Point*> vertexes, normal, textures;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            alfa = j * dimSide;
            if (i == 0) {
                // base
                vertexes.push_back(new Point(0, 0, 0));
                x = radius * sin(alfa + dimSide);
                z = radius * cos(alfa + dimSide);
                vertexes.push_back(new Point(x, 0, z));

                x = radius * sin(alfa);
                z = radius * cos(alfa);
                vertexes.push_back(new Point(x, 0, z));

                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));
                normal.push_back(new Point(0, -1, 0));
            }
            if (i < stacks - 1) {
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                //file << x << " " << (i + 1) * l << " " << z << endl;
                vertexes.push_back(new Point(x, (i + 1) * l, z));
                normal.push_back(new Point(sin(alfa + dimSide), l, cos(alfa + dimSide)));

                x = (radius - ((i + 1) * t)) * sin(alfa);
                z = (radius - ((i + 1) * t)) * cos(alfa);
                //file << x << " " << (i + 1) * l << " " << z << endl;
                vertexes.push_back(new Point(x, (i + 1) * l, z));
                normal.push_back(new Point(sin(alfa), l, cos(alfa)));
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x, i * l, z));
                normal.push_back(new Point(sin(alfa), l, cos(alfa)));

                //file << x << " " << i * l << " " << z << endl;
                vertexes.push_back(new Point(x, i * l, z));
                normal.push_back(new Point(sin(alfa), l, cos(alfa)));
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);
                vertexes.push_back(new Point(x, i * l, z));
                normal.push_back(new Point(sin(alfa + dimSide), l, cos(alfa + dimSide)));
                x = (radius - ((i + 1) * t)) * sin(alfa + dimSide);
                z = (radius - ((i + 1) * t)) * cos(alfa + dimSide);
                vertexes.push_back(new Point(x, (i + 1) * l, z));
                normal.push_back(new Point(sin(alfa + dimSide), l, cos(alfa + dimSide)));

            } else {
                x = (radius - (i * t)) * sin(alfa);
                z = (radius - (i * t)) * cos(alfa);
                vertexes.push_back(new Point(x, i * l, z));
                normal.push_back(new Point(sin(alfa), l, cos(alfa)));
                x = (radius - (i * t)) * sin(alfa + dimSide);
                z = (radius - (i * t)) * cos(alfa + dimSide);


                vertexes.push_back(new Point(x, i * l, z));
                normal.push_back(new Point(sin(alfa + dimSide), l, cos(alfa + dimSide)));
                vertexes.push_back(new Point(0, (i + 1) * l, 0));
                normal.push_back(new Point(sin(alfa + dimSide), l, cos(alfa + dimSide)));


            }
        }
    }
    writeToFile(vertexes, normal, textures, nome);
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

int main(int argc, char* argv[]) {
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
    } else if (argc == 5 && strcmp(argv[1], "patch") == 0) {
        bezierParser(stoi(argv[2]), argv[3], argv[4]);

    } else {
        cout << "Argumentos insuficientes/inválidos" << endl;
        cout << "Para ajuda corra './generator'" << endl;
        //exit(0);
        return 0;
    }
    cout << "Ficheiro guardado em " << PATH << name << endl;

    return 0;
}