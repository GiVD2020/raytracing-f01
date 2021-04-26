#pragma once

#include <vector>
#include <string>

#include <QString>
#include <QFile>
#include <QRegularExpression>


#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "glm/gtx/string_cast.hpp"

#include "Object.h"
#include "Cara.h"
#include "DataService/ReadObj.h"
#include "GeometryBuilders/ObjectFactory.h"

using namespace std;

class BoundaryObject : public Object
{
public:
    BoundaryObject(string s, float data);
    BoundaryObject(const QString &fileName, float data);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
    void aplicaTG(shared_ptr<TG> t);
    virtual void applyAnimation(shared_ptr<CustomAnimation> anim, int nFrame) override;
private:


    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<shared_ptr<Object>> triangles;
    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);

};

