
#include "../headers/bezier.h"


int* patches;
vector<Point*> controls;
int n_patches;
int n_controls;
vector<Point*> vertexes;
vector<Point*> normal;


void writePatch(string fileName);

Point* evalBezierCurve(float t, float* p1, float* p2, float* p3, float* p4) {

    float x, y, z;

    float it = 1.0 - t;

    float b0 = it * it * it;
    float b1 = 3 * t * it * it;
    float b2 = 3 * t * t * it;
    float b3 = t * t * t;

    x = b0 * p1[0] + b1 * p2[0] + b2 * p3[0] + b3 * p4[0];
    y = b0 * p1[1] + b1 * p2[1] + b2 * p3[1] + b3 * p4[1];
    z = b0 * p1[2] + b1 * p2[2] + b2 * p3[2] + b3 * p4[2];

    return new Point(x, y, z);
}


Point* bezierDetermine(float u, float v, int patch) {
    float matrix[4][3], res[4][3];
    int j = 0, k = 0;
    for (int i = 0; i < 16; i++) {
        matrix[j][0] = controls[patches[16 * patch + i]]->getX();
        matrix[j][1] = controls[patches[16 * patch + i]]->getY();
        matrix[j][2] = controls[patches[16 * patch + i]]->getZ();

        j++;

        if (j % 4 == 0) {
            Point* p = evalBezierCurve(u,
                                       matrix[0], matrix[1], matrix[2], matrix[3]
            );
            res[k][0] = p->getX();
            res[k][1] = p->getY();
            res[k][2] = p->getZ();

            k++;
            j = 0;
        }
    }
    return evalBezierCurve(v,
                           res[0],
                           res[1],
                           res[2],
                           res[3]);

}

void toVector(float* a,float * b, float* res){
    res[0] = b[0]- a[0];
    res[1] = b[1]- a[1];
    res[2] = b[2]- a[2];
}

void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float* a) {
    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

void renderBezierPatch(int tess, int n) {
    float shift = 1.0f / tess, u, v, u2, v2;

    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            u = i * shift;
            v = j * shift;
            u2 = (i + 1) * shift;
            v2 = (j + 1) * shift;

            Point* p0 = bezierDetermine(u, v, n);
            Point* p1 = bezierDetermine(u, v2, n);
            Point* p2 = bezierDetermine(u2, v, n);
            Point* p3 = bezierDetermine(u2, v2, n);

            float res[3];
            float res2[3];
            float resfinal[4];
            float a[3] = {p0->getX(),p0->getY(),p0->getZ()};
            float b[3] = {p1->getX(),p1->getY(),p1->getZ()};
            float c[3] = {p2->getX(),p2->getY(),p2->getZ()};
            float d[3] = {p3->getX(),p3->getY(),p3->getZ()};

            toVector(a,c,res);
            toVector(a,d,res2);
            cross(res,res2,resfinal);
            normalize(resfinal);

            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));
            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));
            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));

            vertexes.push_back(p0);
            vertexes.push_back(p2);
            vertexes.push_back(p3);


            //cross(c,a,res); // teste (está ao contrário)
            //normalize(res);

            toVector(a,d,res);
            toVector(a,b,res2);
            cross(res,res2,resfinal);
            normalize(resfinal);


            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));
            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));
            normal.push_back(new Point(resfinal[0],resfinal[1],resfinal[2]));

            vertexes.push_back(p0);
            vertexes.push_back(p3);
            vertexes.push_back(p1);


        }
    }
}



int bezierParser(int tess, string file, string nameFile) {

    string filePath = "../src/Files/" + file;

    string line;
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

    for (int i = 0; i < n_controls; i++) {
        getline(inputFileStream, line);

        istringstream lineStream(line);
        string a, b, c;
        getline(lineStream, a, ',');
        getline(lineStream, b, ',');
        getline(lineStream, c, '\n');
        controls.push_back(new Point(stof(a), stof(b), stof(c)));
        //printf("%f - ",controls[i*3+k]);

        //printf("\n");
    }
    for (int i = 0; i < n_patches; i++)
        renderBezierPatch(tess, i);
    writePatch(nameFile);
}

void writePatch(string fileName) {

    string filePath = "../src/Files/" + fileName;
    ofstream file(filePath);
    file << vertexes.size() << endl;
    for (int i = 0; i < vertexes.size(); i++) {
        file << vertexes[i]->getX() << " " << vertexes[i]->getY() << " " << vertexes[i]->getZ() << endl;
    }
    for (int i = 0; i < normal.size(); i++) {
        file << normal[i]->getX() << " " << normal[i]->getY() << " " << normal[i]->getZ() << endl;
    }
    file.close();

}
