#pragma once

#include <vector>
#include <string>

#include <QString>
#include <QFile>
#include <QRegularExpression>


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.h"
#include "Cara.h"
#include "DataService/ReadObj.h"

using namespace std;

class BoundaryObject : public Object
{
public:
    BoundaryObject(string s, float data);
    BoundaryObject(const QString &fileName, float data);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

private:


    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits

    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);

};

